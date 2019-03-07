#pragma once

#include <Ptole/net/InetAddress.h>
#include <Ptole/net/Socket.h>
#include <Ptole/net/Connection.h>
#include <Ptole/net/Loop.h>
#include <Ptole/net/CallbackDefination.h>

#include<map>
#include "LoopThreadPool.h"

namespace Ptole {
	namespace net {
		class TcpServer {
		public:
			TcpServer(const InetAddress &serverAddress, Loop* loop, int thread_nums = 1);
			void start();

		private:
			/*using MessageCallback = std::function<void(Connection* connPtr, Buffer* buffer)>;*/
			using ConnectionMap = std::map<int, std::shared_ptr<Connection>>;
			static const int kEventListSize = 8;
			void createAndListen();
			void NewConnection(int sockfd, InetAddress& peerAddress);
			InetAddress serverAddress_;
			Socket listenSocket_;
			Loop* loop_;
			ConnectionMap connections_;

			std::unique_ptr<LoopThreadPool> threadpool_;

			MessageCallback msgcb_;
		};
	}
}
