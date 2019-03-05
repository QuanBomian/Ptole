#pragma once

#include <stdint.h>
#include <netinet/in.h>

namespace Ptole {
	namespace net {
		namespace socket_util{
			void fromIpPort2Addr(const char* ip,uint16_t port,struct sockaddr_in* addr);
			void fromIpPort2Addr6(const char *ip, uint16_t port, struct sockaddr_in6* addr6);
			ssize_t read(int fd,void* buf, size_t len);
			ssize_t write(int fd,const void * buf, size_t len);
			void close(int fd);
		}
	}
}
