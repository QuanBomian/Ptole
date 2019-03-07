#pragma once
#include <vector>
#include <memory>


namespace Ptole
{
	namespace net
	{
		class Loop;
		class LoopThread;
		class LoopThreadPool
		{
		public:
			LoopThreadPool(Loop* ownLoop, int thread_nums);
			~LoopThreadPool();
			void Start();
			Loop* consume();
		private:
			Loop* ownLoop_;
			int thread_nums_;
			int next_;
			std::vector<std::unique_ptr<LoopThread>> loop_threads_;
			std::vector<Loop*> loops_;
		};
	}
}
