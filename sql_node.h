#ifndef SQL_NODE_H
#define SQL_NODE_H
#include <pthread/pthread.h>
#include <mysql/mysql.h>
class PollNode
{
private:
	MYSQL* fd;
	pthread_mutex_t lock;
	bool isUsed;
	
public:
	PollNode();
	~PollNode();
	bool isUse();
	void setUse(bool used);
	void close();
	bool try_lock();
	MYSQL* getFd();
};
#endif