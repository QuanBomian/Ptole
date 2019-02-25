#include<Ptole/net/Channel.h>
#include<sys/epoll.h>
using namespace Ptole::net;

void Channel::enableReading() {
	events_ |= EPOLLIN;
	update();
}
void Channel::update(){
	struct epoll_event event;
	event.data.ptr = this;
	event.events = events_;
	epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd_, &event);
}
void Channel::handleEvent(){
	if (revents_ & (EPOLLIN | EPOLLPRI)) {
		if (readingCallback_)
			readingCallback_();
	}
	if(revents_ & EPOLLRDHUP);
	if (revents_ & EPOLLOUT) {
		if (writingCallback_)
			writingCallback_();
	}
}
