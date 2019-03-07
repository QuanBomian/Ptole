#include<Ptole/net/LoopThread.h>
#include<Ptole/net/Loop.h>
using namespace  Ptole::net;

LoopThread::LoopThread():loop_(nullptr),thread_(std::bind(&LoopThread::ThreadFunc, this)),mutexLock_(),condition_(mutexLock_)
{}
LoopThread::~LoopThread()
{
	loop_->quit();
	thread_.join();
}
Loop* LoopThread::getLoop()
{
	{
		MutexLockGuard lock(mutexLock_);
		while(loop_ == nullptr)
		{
			condition_.wait();
		}
		return loop_;

	}
}

void LoopThread::ThreadFunc()
{
	Loop loop;
	{
		MutexLockGuard lock(mutexLock_);
		loop_ = &loop;
		condition_.notify();
	}
	loop.loop();
}


