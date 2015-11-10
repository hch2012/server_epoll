#ifndef SQL_POOL_H
#define SQL_POOL_H
#include "mysql/mysql.h"
#include "sql_node.h"
#include <vector>
#include <string>
using namespace std;
class SqlPool
{
private:
	string host;
	string username;
	string password;
	string database;
	int port;
	int max_num;
	vector<PollNode*> nodeVector;
	PollNode* create_node();
public:
	SqlPool(string &host,string &username,string &password,string &database,int port);
	~SqlPool();
	bool generate(int num);
	PollNode* getConnectiton();
	int node_size();
};

#endif