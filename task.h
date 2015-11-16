#ifndef TASK_H
#define TASK_H
class Task
{
public:
	virtual void run()=0;
	virtual ~Task(){
		
	}
};
#endif