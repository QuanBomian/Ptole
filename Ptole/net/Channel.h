#pragma once

#include<functional>
namespace Ptole {
	namespace net {
		class Channel {
		public:
			using callback = std::function<void()>;
			Channel(int fd,int epollfd):state_(kNotAdded),fd_(fd),epollfd_(epollfd),events_(0),revents_(0){}
			void enableReading();
			void handleEvent();
			void update();
			void setReadingCallback(callback cb) { readingCallback_ = cb; }
			void setRevents(int revents) { revents_ = revents; }
			void setState(int state) {
				state_ = state;
			};
			int fd() { return fd_; }
		private:
			static const int kNotAdded = -1;
			static const int kAdded = 0; //have add to poller
			static const int kRemoved = 1;
			int state_;
			int fd_;
			int events_;
			int revents_;
			int epollfd_;
			callback readingCallback_;
			callback writingCallback_;
		};
	}
}