#include <Ptole/net/TcpServer.h>
#include <Ptole/net/Socket.h>
#include <Ptole/net/Channel.h>
#include<Ptole/net/Loop.h>

#include <sys/epoll.h>
#include <vector>
#include "SocketUtil.h"
using namespace Ptole::net;

TcpServer::TcpServer(const InetAddress &serverAddress, Loop* loop, int thread_nums):
	loop_(loop),
	serverAddress_(serverAddress), 
	listenSocket_(::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0)),
	threadpool_(new LoopThreadPool(loop,thread_nums))
{
}
void TcpServer::createAndListen() {
	
	/*listenSocket_.bind(serverAddress_);
	listenSocket_.listen();
	Channel* listenChannel = new Channel(listenSocket_.fd(),loop_);
	listenChannel->enableReading();
	listenChannel->setReadingCallback(std::bind(&TcpServer::onConnection, this));*/

}

void TcpServer::start() {
	createAndListen();
	threadpool_->Start();
	
}
void TcpServer::NewConnection(int sockfd, InetAddress& peerAddress) {

	Loop* ioLoop = threadpool_->consume();
	std::shared_ptr<Connection> connection = std::make_shared<Connection>(sockfd, loop_, serverAddress_, peerAddress);
	connection->setMessageCallback(msgcb_);
	connections_[sockfd] = connection;

	/*static int connNums = 0;
	
	InetAddress peerAddress;
	int connfd = listenSocket_.accept(peerAddress);
	if (connfd >= 0) {
		Channel* channel = new Channel(connfd,loop_);
		channel->enableReading();
		channel->enableWriting();
		connNums++;
		printf("connection number:%d\n", connNums);
	}*/

}