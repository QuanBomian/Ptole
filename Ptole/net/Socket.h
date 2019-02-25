#pragma once

#include <Ptole/net/InetAddress.h>
#include <fcntl.h>
namespace Ptole {
	namespace net {
		class Socket {
		public:
			explicit Socket(int fd) :fd_(fd) {
				enableReuseAddr();
			}
			~Socket();
			void listen();
			int accept(InetAddress & peerAddress);
			void bind(const InetAddress & localAddress);
			int fd() { return fd_; }
			void enableReuseAddr();
		private:
			const int fd_;
		};

	}
}
