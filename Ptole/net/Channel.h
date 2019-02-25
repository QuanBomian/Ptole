#pragma once

#include<functional>
namespace Ptole {
	namespace net {
		class Channel {
		public:
			using callback = std::function<void()>;
			Channel(int fd,int epollfd):fd_(fd),epollfd_(epollfd),events_(0),revents_(0){}
			void enableReading();
			void handleEvent();
			void update();
			void setReadingCallback(callback cb) { readingCallback_ = cb; }
			void setRevents(int revents) { revents_ = revents; }
		private:
			int fd_;
			int events_;
			int revents_;
			int epollfd_;
			callback readingCallback_;
			callback writingCallback_;
		};
	}
}