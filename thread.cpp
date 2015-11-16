#include "thread.h"
#include "task.h"
#include <queue>
#include "thread_pool.h"
	Thread::Thread(){
		this->id=new pthread_t();
		pthread_create(this->id,NULL,deal,(void*)this);
		this->closed=false;
	}
	Thread::~Thread(){
		pthread_cancel(*this->id);
	}
	pthread_t* Thread::getId(){
		return id;
	}
	void* deal(void* args){
		Thread* thread=static_cast<Thread*>(args);
		while(!thread->isClose()){
			thread->getPool()->lock();
			while(thread->getPool()->taskIsEmpty()){
				thread->getPool()->wait();
			}
			Task* task=thread->getPool()->popTask();
			thread->getPool()->unlock();
			task->run();
			delete task;
		}
		delete thread;
		return NULL;
	}
	void Thread::close(){
		this->closed=false;
	}
	bool Thread::isClose(){
		return this->closed;
	}
	ThreadPool* Thread::getPool(){
		return this->pool;
	}

	void Thread::setPool(ThreadPool* pool){
		this->pool=pool;
	}