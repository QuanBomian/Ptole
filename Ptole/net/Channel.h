#pragma once

#include<functional>

namespace Ptole {
	namespace net {
		class Loop;
		class Channel {
		public:
			using callback = std::function<void()>;
			Channel(int fd, Loop* loop);
			void enableReading();
			void enableWriting();
			void handleEvent();
			void update();
			void setReadingCallback(callback cb) { readingCallback_ = cb; }
			void setWritingCallvack(callback cb) { writingCallback_ = cb; }
			void setRevents(int revents) { revents_ = revents; }
			void setState(int state) {
				state_ = state;
			};
			int fd() { return fd_; }
			int state() { return state_; }
			int events() { return events_; }
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