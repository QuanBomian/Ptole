#pragma once
#include<Ptole/base/Mutex.h>
#include<Ptole/base/Condition.h>
#include<Ptole/base/Thread.h>
using namespace Ptole::base;
namespace Ptole
{
	namespace net
	{
		class LoopThread
		{
		private:
			Thread thread_;
			MutexLock mutexLock_;
			Condition condition;
		public:
			LoopThread();
			~LoopThread();
		};
		
	}
}
