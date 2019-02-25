#pragma once

#include<netinet/in.h>
#include<stdint.h>

#include<string>
namespace Ptole {
	namespace net {
		class InetAddress {
		public:
			InetAddress() = default;
			InetAddress(const std::string ip, uint16_t port, bool ipv6 = false);
			explicit InetAddress(uint16_t port, bool ipv6 = false);
			const struct sockaddr* SockAddr() const{
				return static_cast<const struct sockaddr*>(static_cast<const void*>(&addr6_));
			}
			void setSockAddr(const sockaddr_in6& addr6) { addr6_ = addr6; }
		private:
			union
			{
				struct sockaddr_in addr_;
				struct sockaddr_in6 addr6_;
			};
		};
	} //namespace net
} //namespace Ptole
