#include <Ptole/base/Thread.h>
using namespace Ptole::base;


void* run(void* args)
{
	Thread* t = (Thread*)args;
	(t->task())();
}
void Thread::start()
{
	started = true;
	int ret = pthread_create(&tid_, nullptr, &run, this);
	if(ret)
	{
		started = false;
		fprintf(stderr, "failed to create pthread");
		exit(-1);
	}
}
void Thread::join()
{
	joined = true;
	pthread_join(tid_, nullptr);
}
Thread::~Thread()
{
	if(started && !joined)
	{
		pthread_detach(tid_);
	}
}


