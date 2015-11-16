	#include <iostream>
	#include "one_task.h"
	#include "log4c.h"
	OneTask::OneTask(std::string &msg){
		this->msg=msg;
	}
	OneTask::~OneTask(){

	}
	void OneTask::run(){
		usleep(100000);
		Log4C* log=new Log4C();
		log->out(msg);
	}