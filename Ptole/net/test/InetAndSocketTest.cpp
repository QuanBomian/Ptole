#include <Ptole/net/InetAddress.h>
#include <Ptole/net/Socket.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

using namespace Ptole::net;
int main() {
	char buf[1024];
	bzero(buf,sizeof(buf));
	InetAddress serverAddress(8888);
	int socketfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
	Socket server(socketfd);
	server.bind(serverAddress);
	server.listen();
	InetAddress peerAddress;
	while (1) {
		int connfd = server.accept(peerAddress);
		if (connfd >= 0) {
			int n = read(connfd, buf, sizeof(buf));
			if (n > 0) {
				printf("%s\n", buf);
			}
		}
	}

}