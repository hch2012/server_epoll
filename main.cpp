#include <iostream>
#include "sql_pool.h"
#include <string>
#include <cstdio>
#include <unistd.h>
using namespace std;
SqlPool* pool=NULL;
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