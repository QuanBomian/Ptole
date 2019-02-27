#include <Ptole/net/TcpServer.h>
#include <Ptole/net/Socket.h>
#include <Ptole/net/Channel.h>
#include<Ptole/net/Loop.h>

#include <sys/epoll.h>
#include <vector>
using namespace Ptole::net;

int TcpServer::createAndListen() {
	
	listenSocket_.bind(serverAddress_);
	listenSocket_.listen();
	Channel* listenChannel = new Channel(listenSocket_.fd(),loop_);
	listenChannel->enableReading();
	listenChannel->setReadingCallback(std::bind(&TcpServer::onConnection, this));

}

void TcpServer::start() {
	createAndListen();
	
}
void TcpServer::onConnection() {
	static int connNums = 0;
	
	InetAddress peerAddress;
	int connfd = listenSocket_.accept(peerAddress);
	if (connfd >= 0) {
		Channel* channel = new Channel(connfd,loop_);
		channel->enableReading();
		connNums++;
		printf("connection number:%d\n", connNums);
	}

}