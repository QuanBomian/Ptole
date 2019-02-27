#pragma once
#include<vector>
#include<map>
#include<sys/epoll.h>
#include<unistd.h>

namespace Ptole {
	namespace net {
		class Channel;
		class Loop;
		class Epoller {
		private:
			static const int kNotAdded = -1;
			static const int kAdded = 0; //have add to poller
			//static const int kRemoved = 1;
			static const int kEventListSize = 8;
			typedef std::vector<struct epoll_event> EventList;
			typedef std::vector<Channel*> ChannelList;
			typedef std::map<int, Channel*> ChannelMap;
			int epollfd_;
			EventList events_;
			ChannelMap focusedChannels_;
			Loop* loop_;
		public:
			static Epoller* Poller(Loop* loop);
			
			Epoller(Loop* loop);
			~Epoller();
			void poll(ChannelList* activeChannels);
			void addChannel(Channel* channel);
			void removeChannel(Channel* channel);
			void updateChannel(Channel* channel);
			void updatePoller(int epollOp, Channel* channel);
		
		};
	}
}