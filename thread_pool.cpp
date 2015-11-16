#include "thread_pool.h"
	std::queue<Task*> taskQueue;
	std::vector<Thread*> threadVector;
	ThreadPool::ThreadPool(int num){
		pthread_mutex_init(&this->mutex,NULL);
		pthread_cond_init(&this->cond, NULL);
		for(int i=0;i<num;i++){
			this->threadVector.push_back(new Thread());
			threadVector[threadVector.size()-1]->setPool(this);
		}
	}
	ThreadPool::~ThreadPool(){
		pthread_mutex_destroy(&this->mutex);
		pthread_cond_destroy(&this->cond);
	}
	void ThreadPool::lock(){
		pthread_mutex_lock(&this->mutex);
	}
	void ThreadPool::unlock(){
		pthread_mutex_unlock(&this->mutex);
	}
	void ThreadPool::wait(){
		pthread_cond_wait(&this->cond,&this->mutex);
	}
	void ThreadPool::signal(){
		pthread_cond_signal(&this->cond);
	}
	void ThreadPool::pushTask(Task* task){
		lock();
		this->taskQueue.push(task);
		signal();
		unlock();
	}
	Task* ThreadPool::popTask(){
		Task* task=NULL;
		if(!taskQueue.empty()){
			task=taskQueue.front();
			taskQueue.pop();
		}
		return task;

	}
	void ThreadPool::addThread(Thread* thread){
		this->threadVector.push_back(thread);
	}
	bool ThreadPool::taskIsEmpty(){
		return this->taskQueue.empty();
	}