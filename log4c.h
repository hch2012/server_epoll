#ifndef LOG_4_C_H
#define LOG_4_C_H
#include <string>
#include <pthread/pthread.h>
class Log4C
{
private:
	pthread_mutex_t mutex;
public:
	Log4C();
	~Log4C();
	void out(std::string &out);
};

#endif