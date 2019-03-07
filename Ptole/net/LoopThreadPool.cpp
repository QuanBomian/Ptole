#include<Ptole/net/LoopThreadPool.h>

using namespace Ptole::net;

LoopThreadPool::LoopThreadPool(Loop* ownLoop,int thread_nums):ownLoop_(ownLoop),thread_nums_(thread_nums),next_(0){}
LoopThreadPool::~LoopThreadPool(){}
void LoopThreadPool::Start()
{
	for(int i =0;i<thread_nums;i++)
	{
		std::unique_ptr<LoopThread> t = (new LoopThread());
		loops_.push(t->getLoop());
		loop_threads.push(std::move(t));
	
	}
}
Loop* LoopThreadPool::consume()
{
	Loop* loop = ownloop_;
	if (!loops_.empty())
	{
		loop = loops_[next_];
		next_ = (next_ + 1) % thread_num_;
	}
	return loop;
}