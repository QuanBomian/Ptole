#pragma once
#include<vector>
#include<unordered_map>
#include<sys/epoll.h>
#include<Ptole/net/Channel.h>
#include<Ptole/net/Loop.h>
namespace Ptole {
	namespace net {
		class Epoller {
		public:
			Epoller(Loop* loop):loop_(loop),epollfd_(::epoll_create1(EPOLL_CLOEXEC)),events_(kInitEventListSize){
			}
			~Epoller();
			void poll();
			void addChannel(Channel* channel);
			void removeChannel(Channel* channel);
			void updateChannel(Channel* channel);
			void updatePoller();
		private:
			static const int kNotAdded = -1;
			static const int kAdded = 0; //have add to poller
			//static const int kRemoved = 1;
			static const int kInitEventListSize = 8;
			typedef std::vector<struct epoll_event> EventList;
			typedef std::vector<Channel*> ChannelList;
			typedef std::unordered_map<int, Channel*> ChannelMap;
			int epollfd_;
			EventList events_;
			ChannelMap focusedChannels_;
			Loop* loop_;
		};
	}
}