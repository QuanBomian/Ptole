#pragma once

#include <pthread.h>

#include <functional>
namespace Ptole
{
	
	namespace base
	{
		void* run(void* args);
		class Thread
		{
		private:
			using ThreadFunc = std::function<void()>;
			pthread_t tid_;
			pid_t pid_;
			ThreadFunc task_;
			bool joined;
			bool started;
		public:
			Thread(ThreadFunc task) :task_(task)
			{
			}
			~Thread();
			ThreadFunc task() { return task_; }
			void start();
			void join();

		};
		
	}
}
