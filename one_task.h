#ifndef ONE_TASK_H
#define ONE_TASK_H

#include <unistd.h>
#include "task.h"
#include <string>
class OneTask:public Task
{

private:
	std::string msg;
public:
	OneTask(std::string &msg);
	~OneTask();
	void run();
};


#endif