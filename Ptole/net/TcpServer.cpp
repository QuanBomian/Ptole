#include <Ptole/net/TcpServer.h>
#include <Ptole/net/Socket.h>
#include <Ptole/net/Channel.h>

#include <sys/epoll.h>
#include <vector>
using namespace Ptole::net;

int TcpServer::createAndListen() {
	
	listenSocket_.bind(serverAddress_);
	listenSocket_.listen();
	epollfd_ = epoll_create1(EPOLL_CLOEXEC);
	Channel* listenChannel = new Channel(listenSocket_.fd(), epollfd_);
	listenChannel->enableReading();
	listenChannel->setReadingCallback(std::bind(&TcpServer::onConnection, this));

}

void TcpServer::start() {
	createAndListen();
	struct epoll_event eventList[kEventListSize];
	
	while (1) {
		std::vector<Channel*> channelList;
		int fds = epoll_wait(epollfd_, eventList, kEventListSize, -1);
		if (fds < 0) {
			exit(-1);
		}
		for (int i = 0; i < fds; ++i) {
			Channel* data = static_cast<Channel*>(eventList[i].data.ptr);
			data->setRevents(eventList[i].events);
			channelList.push_back(data);
		}
		for (int i = 0; i < channelList.size(); ++i) {
			channelList[i]->handleEvent();
		}
	}
}
void TcpServer::onConnection() {
	static int connNums = 0;
	
	InetAddress peerAddress;
	int connfd = listenSocket_.accept(peerAddress);
	if (connfd >= 0) {
		Channel* channel = new Channel(epollfd_, connfd);
		channel->enableReading();
		connNums++;
		printf("connection number:%d\n", connNums);
	}

}