#pragma once
#include<vector>
#include<memory>
#include<Ptole/net/Channel.h>
#include<Ptole/net/Epoller.h>
namespace Ptole {
	namespace net {
		class Loop {
		public:
			Loop():poller(new Epoller(this)) {}
			void loop();
			void updateChannel(Channel* channel);
			void addChannel(Channel* channel);
			void removeChannel(Channel* channel);
		private:
			std::vector<Channel> activeChannels_;
			std::unique_ptr<Epoller> poller;
		};
	}
}