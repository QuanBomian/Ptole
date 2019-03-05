#pragma once
#include <Ptole/net/Buffer.h>
#include <Ptole/net/Socket.h>
#include <Ptole/net/Channel.h>
#include <Ptole/net/InetAddress.h>
#include <Ptole/net/CallbackDefination.h>
#include <memory>
#include <functional>

namespace  Ptole
{
	namespace net
	{
		class Loop;
		class Connection
		{
		private:
			static const size_t kMaxLine = 1024;
			/*using Callback = std::function<void()>;
			using MessageCallback = std::function<void(Connection* connPtr, Buffer* buffer)>;*/
			std::unique_ptr<Socket> socket_;
			std::unique_ptr<Channel> channel_;
			Buffer readBuffer_;
			Buffer writeBuffer_;
			Loop* loop_;
			InetAddress localAddress_;
			InetAddress peerAddress_;
			MessageCallback messageCallback_;
		public:
			Connection(int sockfd, Loop* loop, InetAddress loclAddress, InetAddress peerAddress);
			void setMessageCallback(MessageCallback cb) { messageCallback_ = cb; }
			void handleReading();
			void handleWriting();

		


		};
		
	}
}
