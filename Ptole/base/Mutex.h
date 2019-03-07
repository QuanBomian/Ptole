#pragma once
#include<pthread.h>
namespace Ptole
{
	namespace base
	{
		class MutexLock
		{
		private:
			pthread_mutex_t mutex_;
		public:
			MutexLock()
			{
				pthread_mutex_init(&mutex_, nullptr);

			}
			~MutexLock()
			{
				pthread_mutex_destroy(&mutex_);
			}
			void lock()
			{
				pthread_mutex_lock(&mutex_);
			}
			void unlock()
			{
				pthread_mutex_unlock(&mutex_);
			}
			pthread_mutex_t* mutex()
			{
				return &mutex_;
			}

		};

		class MutexLockGuard
		{
		private:
			MutexLock& mutexLock_;
		public:
			MutexLockGuard(MutexLock& mutexLock) :
				mutexLock_(mutexLock)
			{
				mutexLock.lock();
			}
			~MutexLockGuard() {
				mutexLock_.unlock();
			}
		};
		
	}
}
