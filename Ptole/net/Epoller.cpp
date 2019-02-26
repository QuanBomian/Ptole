#include<Ptole/net/Epoller.h>
#include<Ptole/net/Channel.h>

#include<sys/epoll.h>
using namespace Ptole::net;
void Epoller::poll(ChannelList* channels) {
	int fds = epoll_wait(epollfd_, &(*(events_.begin())), kEventListSize, -1);
	for (int i = 0; i < fds, i++) {
		Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
		channel->set_revents(events_[i].events);
		channels->push_back(channel);
	}
}
void Epoller::addChannel(Channel* channel) {
	focusedChannels.insert(channel->fd(), channel);
	channel->setState(kAdded);
	updatePoller(EPOLL_CTL_ADD, channel);
}
void Epoller::removeChannel(Channel* channel) {
	if (channel->state() == kAdded) {
		int fd = channel->fd();
		auto it = focusedChannels_.find(fd);
		if (it != focusedChannels_.end()) {
			focusedChannels.erase(fd);
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
	else if (state = kAdded) {
		auto it = focusedChannels.find(channel->fd());
		if (it != focusedChannels.end()) {
			focusedChannels[channel->fd()] = channel;
		}
		updatePoller(EPOLL_CTL_MOD, channel);
	}
}
void Epoller::updatePoller(int epollOp,Channel* channel) {
	struct epoll_event event;
	event.data.ptr = this;
	event.events = events_;
	int ret = epoll_ctl(epollfd_, epollOp, channel->fd(), &event);
	if ( ret < 0){
		fprintf(stderr, " ");
		exit(-1);
	}
}
EPoller::~EPollPoller()
{
	::close(epollfd_);
}