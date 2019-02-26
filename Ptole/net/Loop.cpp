#include<Ptole/net/Loop.h>
#include<Ptole/net/Channel.h>
using namespace Ptole::net;
void Loop::loop() {
	poller->poll(&activeChannels_);
	for (Channel* channels : activeChannels_) {
		channels->handleEvent();
	}
}
void Loop::updateChannel(Channel* channel) {
	poller->updateChannel(channel);
}
