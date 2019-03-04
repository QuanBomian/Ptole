#pragma once
#include <Ptole/net/Buffer.h>
#include <Ptole/net/Socket.h>
#include <Ptole/net/Channel.h>
#include <Ptole/net/InetAddress.h>
#include <memory>
#include <functional>

namespace  Ptole
{
	namespace net
	{
		class Loop;
		class Connection
		{
		public:
			Connection(int sockfd, Loop* loop, InetAddress loclAddress, InetAddress peerAddress);

		private:
			typedef std::function<void()> Callback;
			std::unique_ptr<Socket> socket_;
			std::unique_ptr<Channel> channel_;
			Buffer readBuffer_;
			Buffer writeBuffer_;
			Loop* loop_;
			InetAddress localAddress_;
			InetAddress peerAddress_;
			Callback readingCallback_;
			Callback writingCallback_;


		};
		
	}
}
