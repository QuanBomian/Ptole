#include <Ptole/net/Connection.h>
#include <Ptole/net/SocketUtil.h>
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
using namespace  Ptole::net;
using namespace Ptole::net;
Ptole::net::Connection::Connection(int sockfd, Loop * loop, InetAddress localAddress, InetAddress peerAddress):
socket_(new Socket(sockfd)),loop_(loop),localAddress_(localAddress),peerAddress_(peerAddress)
{
	channel_->setReadingCallback(std::bind(&Connection::handleReading, this));
	channel_->setWritingCallvack(std::bind(&Connection::handleWriting, this));
}

void Connection::handleReading()
{
	int fd = channel_->fd();
	ssize_t readingBytes;
	char line[kMaxLine];
	bzero(line,kMaxLine);
	if(readingBytes = socket_util::read(fd, line, kMaxLine) <= 0)
	{
		if(errno == ECONNRESET)
		{
			fprintf(stderr, "Connection Reset\n");
			socket_util::close(fd);
			return;
		}
		fprintf(stderr, "reading zero bytes");
		socket_util::close(fd);
		return;
	}
	else
	{
		std::string str(line, readingBytes);
		readBuffer_.append(str);
		messageCallback_(this, &readBuffer_);
	}
}
void Connection::handleWriting()
{
		const int sockfd = channel_->fd();
		ssize_t n = socket_util::write(sockfd, writeBuffer_.peek(), writeBuffer_.readableBytes());
		if (n > 0)
		{
			writeBuffer_.retrieve(n);
			if (writeBuffer_.readableBytes() == 0)
			{
				channel_->disableWriting();
			}
		}
		else
		{
			fprintf(stderr, "write error on fd %d", channel_->fd());
			exit(-1);
		}
	
}

