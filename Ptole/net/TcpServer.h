#pragma once

#include <Ptole/net/InetAddress.h>
#include <Ptole/net/Socket.h>
namespace Ptole {
	namespace net {
		class TcpServer {
		public:
			TcpServer(const InetAddress &serverAddress):
				serverAddress_(serverAddress),listenSocket_(::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0)){
			}
			void start();

		private:
			static const int kEventListSize = 100;
			int createAndListen();
			void onConnection();
			InetAddress serverAddress_;
			Socket listenSocket_;
			int epollfd_;
		};
	}
}
