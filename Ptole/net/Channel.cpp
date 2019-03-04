#include<Ptole/net/Channel.h>
#include<Ptole/net/Loop.h>
#include<sys/epoll.h>
using namespace Ptole::net;

Channel::Channel(int fd,Loop* loop):loop_(loop), state_(kNotAdded), fd_(fd), events_(0), revents_(0){}
void Channel::enableReading() {
	events_ |= EPOLLIN;
	update();
}

void Channel::enableWriting()
{
	events_ |= EPOLLOUT;
	update();
}

void Channel::update(){
		loop_->updateChannel(this);
	//struct epoll_event event;
	//event.data.ptr = this;
	//event.events = events_;
	//epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd_, &event);
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
