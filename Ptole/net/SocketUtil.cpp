#include <Ptole/net/SocketUtil.h>

#include <strings.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
using namespace Ptole::net;

void socket_util::fromIpPort2Addr(const char* ip, uint16_t port, struct sockaddr_in* addr) {
	bzero(addr, sizeof(struct sockaddr_in));
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
	int ret = ::inet_pton(AF_INET, ip, &addr);
	if (ret <= 0) {
		fprintf(stderr, "%s:%s:%d", __FILE__, "socket_util::fromIpPort2Addr", __LINE__);
		exit(-1);
	}
}
void socket_util::fromIpPort2Addr6(const char* ip, uint16_t port, struct sockaddr_in6* addr6) {

	bzero(addr6, sizeof(struct sockaddr_in6));
	addr6->sin6_family = AF_INET6;
	addr6->sin6_port = htons(port);
	int ret = ::inet_pton(AF_INET6, ip, &addr6);
	if (ret <= 0) {
		fprintf(stderr, "%s:%s:%d", __FILE__, "socket_util::fromIpPort2Add6", __LINE__);
		exit(-1);
	}
}