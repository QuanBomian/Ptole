#include <Ptole/net/InetAddress.h>
#include <Ptole/net/SocketUtil.h>

#include <strings.h>



using namespace Ptole::net;
InetAddress::InetAddress(std::string ip, uint16_t port, bool ipv6) {
	if (ipv6) {
		socket_util::fromIpPort2Addr6(ip.c_str(), port, &addr6_);
	}
	else {
		socket_util::fromIpPort2Addr(ip.c_str(), port, &addr_);
	}

}

InetAddress::InetAddress(uint16_t port, bool ipv6) {
	if (ipv6) {
		bzero(&addr6_, sizeof(struct sockaddr_in6));
		addr6_.sin6_family = AF_INET6;
		addr6_.sin6_port = htons(port);
		addr6_.sin6_addr = in6addr_any;

	}
	bzero(&addr_, sizeof (struct sockaddr_in));
	addr_.sin_family = AF_INET;
	addr_.sin_port = htons(port);
	addr_.sin_addr.s_addr = INADDR_ANY;
}
