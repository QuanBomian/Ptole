#include <Ptole/net/Socket.h>
#include <sys/socket.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
using namespace Ptole::net;
Socket::~Socket() { ::close(fd_); }
void Socket::bind(const InetAddress &localAddress) {
	int ret = ::bind(fd_,localAddress.SockAddr(), static_cast<socklen_t>(sizeof (struct sockaddr_in6)));
	if (ret < 0) {
		fprintf(stderr," ");
		exit(-1);
	}
}
int Socket::accept(InetAddress & peerAddress) {
	socklen_t addrlen;
	bzero(&addrlen, sizeof(socklen_t));
	struct sockaddr_in6 addr6;
	bzero(&addr6, sizeof (struct sockaddr_in6));
	int connfd = ::accept4(fd_, 
		static_cast<struct sockaddr*>(static_cast<void*>(&addr6)), 
		&addrlen,SOCK_NONBLOCK|SOCK_CLOEXEC);
	if (connfd < 0) {
		switch (errno)
		{
		case EAGAIN:
		case EINTR:
			break;
		default:
			fprintf(stderr, " ");
			exit(-1);
		}
	}
	if(connfd >= 0)
	peerAddress.setSockAddr(addr6);
	return connfd;
}
void Socket::listen() {
	int ret = ::listen(fd_,SOMAXCONN);
	if(ret < 0) {
		fprintf(stderr," listen error");
		exit(-1);
	}
}

void Socket::enableReuseAddr() {
	int reuse = 1;
	setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

}
