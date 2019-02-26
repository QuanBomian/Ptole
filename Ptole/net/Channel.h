#pragma once

#include<functional>
#include<Ptole/net/Loop.h>
namespace Ptole {
	namespace net {
		class Channel {
		public:
			using callback = std::function<void()>;
			Channel(int fd,Loop* loop):loop_(loop),state_(kNotAdded),fd_(fd),events_(0),revents_(0){}
			void enableReading();
			void handleEvent();
			void update();
			void setReadingCallback(callback cb) { readingCallback_ = cb; }
			void setRevents(int revents) { revents_ = revents; }
			void setState(int state) {
				state_ = state;
			};
			int fd() { return fd_; }
			int state() { return state_; }
		private:
			static const int kNotAdded = -1;
			//static const int kAdded = 0; //have add to poller
			//static const int kRemoved = 1;
			int state_;
			int fd_;
			int events_;
			int revents_;
			//int epollfd_;
			callback readingCallback_;
			callback writingCallback_;
			Loop* loop_;
		};
	}
}