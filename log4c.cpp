#include "log4c.h"
#include <cstdio>

void Log4C::out(std::string &out){
	pthread_mutex_lock(&mutex);
	printf("%s\n",out.c_str());
	pthread_mutex_unlock(&mutex);

}
Log4C::Log4C(){
	pthread_mutex_init(&mutex,NULL);
}
Log4C::~Log4C(){
	pthread_mutex_destroy(&mutex);
}