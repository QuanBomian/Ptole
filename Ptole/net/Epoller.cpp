#include<Ptole/net/Epoller.h>
#include<Ptole/net/Channel.h>
#include<Ptole/net/Loop.h>
#include<sys/epoll.h>
#include <stdlib.h>
using namespace Ptole::net;
Epoller::Epoller(Loop* loop) :loop_(loop), epollfd_(::epoll_create1(EPOLL_CLOEXEC)), events_(kEventListSize){}
void Epoller::poll(ChannelList* channels) {
	int fds = epoll_wait(epollfd_, &(*(events_.begin())), kEventListSize, -1);
	for (int i = 0; i < fds; i++) {
		Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
		channel->setRevents(events_[i].events);
		channels->push_back(channel);
	}
}
void Epoller::addChannel(Channel* channel) {
	focusedChannels_.insert_or_assign(channel->fd(), channel);
	channel->setState(kAdded);
	updatePoller(EPOLL_CTL_ADD, channel);
}
void Epoller::removeChannel(Channel* channel) {
	if (channel->state() == kAdded) {
		int fd = channel->fd();
		auto it = focusedChannels_.find(fd);
		if (it != focusedChannels_.end()) {
			focusedChannels_.erase(fd);
			channel->setState(kNotAdded);
			updatePoller(EPOLL_CTL_DEL, channel);
		}
	}
}
void Epoller::updateChannel(Channel* channel) {
	int state = channel->state();
	if (state == kNotAdded) {
		addChannel(channel);
	}
	else if (state == kAdded) {
		auto it = focusedChannels_.find(channel->fd());
		if (it != focusedChannels_.end()) {
			focusedChannels_[channel->fd()] = channel;
		}
		updatePoller(EPOLL_CTL_MOD, channel);
	}
}
void Epoller::updatePoller(int epollOp,Channel* channel) {
	struct epoll_event event;
	event.data.ptr = channel;
	event.events = channel->events();
	int ret = epoll_ctl(epollfd_, epollOp, channel->fd(), &event);
	if ( ret < 0){
		fprintf(stderr, " ");
		exit(-1);
	}
}
Epoller::~Epoller()
{
	::close(epollfd_);
}

Epoller*  Epoller::Poller(Loop* loop) {
	return new Epoller(loop);
}