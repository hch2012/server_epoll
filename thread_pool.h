#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include "task.h"
#include "thread.h"
#include <queue>
#include <vector>
class ThreadPool
{
private:
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	std::queue<Task*> taskQueue;
	std::vector<Thread*> threadVector;
public:
	ThreadPool(int num=5);
	~ThreadPool();
	void lock();
	void unlock();
	void wait();
	void signal();
	void pushTask(Task* task);
	Task* popTask();
	void addThread(Thread* thread);
	bool taskIsEmpty();
};
#endif