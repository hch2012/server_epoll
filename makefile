objs=main.o sql_node.o sql_pool.o
mysql_config=`mysql_config --include`  `mysql_config --libs`

main:${objs}
	g++ -g -o  main  ${objs} ${mysql_config}
main.0:
	g++ -g -c main.cpp ${mysql_config}
sql_node.o:sql_node.h
	g++ -g -c sql_node.cpp sql_node.h ${mysql_config}
sql_pool.o:sql_pool.h
	g++ -g -c sql_pool.cpp sql_pool.h ${mysql_config}