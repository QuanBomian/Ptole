#include<Ptole/net/Loop.h>
#include<Ptole/net/Channel.h>
#include<Ptole/net/Epoller.h>
using namespace Ptole::net;
Loop::Loop():poller_(Epoller::Poller(this)){}
void Loop::loop() {
	poller_->poll(&activeChannels_);
	while (1) {
		for (Channel* channel : activeChannels_) {
			channel->handleEvent();
		}
	}
}
Loop::~Loop() {

}
void Loop::updateChannel(Channel* channel) {
	poller_->updateChannel(channel);
}
