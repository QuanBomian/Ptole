#pragma once
#include<vector>
#include<memory>

namespace Ptole {
	namespace net {
		class Channel;
		class Epoller;
		class Loop {
		public:
			Loop();
			~Loop();
			void loop();
			void updateChannel(Channel* channel);
			void addChannel(Channel* channel);
			void removeChannel(Channel* channel);
		private:
			typedef std::vector<Channel*> ChannelList;
			ChannelList activeChannels_;
			std::unique_ptr<Epoller> poller_;
		};
	}
}