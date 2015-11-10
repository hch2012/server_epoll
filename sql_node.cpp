#include "sql_pool.h"
	PollNode::PollNode(){
		this->fd=new MYSQL();
		mysql_init(this->fd);
		pthread_mutex_init(&this->lock,NULL);
		this->isUsed=false;
	}
	PollNode::~PollNode(){
		delete this->fd;
	}
	bool PollNode::isUse(){
		return this->isUsed;
	}
	void PollNode::setUse(bool used){
		this->isUsed=used;
	}
	MYSQL* PollNode::getFd(){
		return this->fd;
	}
	void PollNode::close(){
		this->isUsed=false;
		pthread_mutex_unlock(&this->lock);
	}
	bool PollNode::try_lock(){
		return pthread_mutex_trylock(&this->lock)==0;
	}