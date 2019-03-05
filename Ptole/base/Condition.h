#pragma once
#include <Ptole/base/Mutex.h>
#include <condition_variable>
class Condition
{
private:
	MutexLock& mutexLock_;
	pthread_cond_t condition_;
public:
	Condition(MutexLock mutexLock):mutexLock_(mutexLock)
	{
		pthread_cond_init(&condition_, nullptr);
	}
	~Condition()
	{
		pthread_cond_destroy(&condition_);
	}
	void notify()
	{
		pthread_cond_signal(&condition_);
	}
	void notifyAll()
	{
		pthread_cond_broadcast(&condition_);
	}
	void wait()
	{
		pthread_cond_wait(&condition_, mutexLock_.mutex());
	}


};