#pragma once

#include <Ptole/net/InetAddress.h>
#include <Ptole/net/Socket.h>
#include <Ptole/net/Connection.h>
#include <Ptole/net/Loop.h>
#include <Ptole/net/CallbackDefination.h>

#include<map>
namespace Ptole {
	namespace net {
		class TcpServer {
		public:
			TcpServer(const InetAddress &serverAddress,Loop* loop):
				loop_(loop),
				serverAddress_(serverAddress),listenSocket_(::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0)){
			}
			void start();

		private:
			/*using MessageCallback = std::function<void(Connection* connPtr, Buffer* buffer)>;*/
			using ConnectionMap = std::map<int, Connection>;
			static const int kEventListSize = 8;
			void createAndListen();
			void onConnection();
			InetAddress serverAddress_;
			Socket listenSocket_;
			Loop* loop_;
			ConnectionMap connections_;

		};
	}
}
