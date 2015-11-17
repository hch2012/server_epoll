#include <iostream>
#include "sql_pool.h"
#include <string>
#include <cstdio>
#include <unistd.h>
#include "thread_pool.h"
#include "one_task.h"
#include <sstream>
#include <sys/epoll.h>
using namespace std;
SqlPool* pool=NULL;
void testThreadPool(int argc, char const *argv[]);
void testEpoll();
void* insert(void* args){
	//printf("111");
	char sql[]="insert into bbb(name) values('ccc')";
	//char* sql;
	//sprintf(sql,format,*(int*)args);
	//printf("%s",sql);
	PollNode* node=pool->getConnectiton();
	mysql_query(node->getFd(),sql);
	node->close();
	return NULL;
}
int main(int argc, char const *argv[])
{	
	testEpoll();
	//testThreadPool(argc,argv);
}
void testThreadPool(int argc, char const *argv[]){
	ThreadPool* pool=new ThreadPool(1000);
	string str="task ";
	ostringstream stream;
	for(int i=0;i<100000;i++){
		stream<<str<<i;
		string tmp=stream.str();
		stream.str("");
		pool->pushTask(new OneTask(tmp));
	}
	sleep(1000);
}

void testSqlPool(int argc, char const *argv[]){
	string host="127.0.0.1";
	string username="root";
	string password="hch123";
	string database="aaa";
	if(argc>1)
		host=argv[1];

	pool=new SqlPool(host,username, password, database,3306);
	pool->generate(5);
	pthread_t t[20];
	for(int i=0;i<15;i++){
		int a=i;
		usleep(100);
		pthread_create(&t[i],NULL,insert,NULL);	
	}
	for(int i=0;i<15;i++){
		pthread_join(t[i],NULL);
	}
	cout<<pool->node_size()<<endl;
}
void testEpoll(){
    int epfd,nfds;
    struct epoll_event ev,events[5];//ev用于注册事件，数组用于返回要处理的事件
    epfd=epoll_create(1);//只需要监听一个描述符——标准输入
    ev.data.fd=STDIN_FILENO;
    ev.events=EPOLLIN;//监听读状态同时设置ET模式
    epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&ev);//注册epoll事件
    for(;;)
   	{
	     nfds=epoll_wait(epfd,events,5,-1);
	     for(int i=0;i<nfds;i++)
	     {
	        if(events[i].data.fd==STDIN_FILENO)
	           cout<<"hello world!"<<endl;
	     }
   	}
}

