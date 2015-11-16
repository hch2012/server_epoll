#ifndef THREAD_H
#define THREAD_H
#include <pthread/pthread.h>
class ThreadPool;
class Thread
{
public:
	Thread();
	~Thread();
	pthread_t* getId();
	void close();
	bool isClose();
	ThreadPool* getPool();
	void setPool(ThreadPool* pool);
private:
	pthread_t* id;
	bool closed;
	ThreadPool* pool;
};
static void* deal(void* args);
#endif