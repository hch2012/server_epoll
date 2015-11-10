#include "sql_pool.h"
	
	PollNode* SqlPool::create_node(){
		PollNode* node=new PollNode();
		MYSQL* result=mysql_real_connect(node->getFd(),host.c_str(),username.c_str(), password.c_str(), database.c_str(),port, NULL, 0);
		if(result==NULL)
			return NULL;
		mysql_set_character_set(node->getFd(), "utf8");
		return node;
	}
	SqlPool::SqlPool(string &host,string &username,string &password,string &database,int port):max_num(20){
		this->host=host;
		this->username=username;
		this->password=password;
		this->database=database;
		this->port=port;
	}
	SqlPool::~SqlPool(){

	}
	bool SqlPool::generate(int num){
		if(num>max_num)
			return false;
		while(num--){
			PollNode* node=create_node();
			if(node==NULL)
				return false;
			this->nodeVector.push_back(node);
		}
		return true;
	}
	PollNode* SqlPool::getConnectiton(){
		PollNode* node=NULL;
		int times_out=100;
		while(node==NULL && times_out--){
			for(int i=0;i<nodeVector.size();i++){
				if(!nodeVector[i]->isUse()){
					if(!nodeVector[i]->try_lock()){
						nodeVector[i]->setUse(true);
						node=nodeVector[i];
						break;
					}
				}
			}
			if(node==NULL){
				if(nodeVector.size()<max_num){
					node=create_node();
					if(node==NULL)
						return NULL;
					this->nodeVector.push_back(node);
				}
			}
		}
		return node;
	}
	int SqlPool::node_size(){
		return this->nodeVector.size();
	}
