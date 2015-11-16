objs=main.o sql_node.o sql_pool.o one_task.o thread.o thread_pool.o log4c.o
mysql_config=`mysql_config --include`  `mysql_config --libs`
debug=-g

main:${objs}
	g++ -g -o  main  ${objs} ${mysql_config} ${debug}
main.o:
	g++ -g -c main.cpp ${mysql_config} ${debug}
sql_node.o:sql_node.h
	g++ -g -c sql_node.cpp sql_node.h ${mysql_config} ${debug}
sql_pool.o:sql_pool.h
	g++ -g -c sql_pool.cpp sql_pool.h ${mysql_config} ${debug}
thread_pool.o:thread_pool.h
	g++ -g -c thread_pool.cpp thread_pool.h ${debug}
thread.o:thread.h
	g++ -g -c thread.cpp thread.h ${debug}
one_task.o:task.h
	g++ -g -c one_task.cpp ${debug}
log4c.o:log4c.h
	g++ -g -c log4c.cpp log4c.h ${debug}
clean:
	rm *.o;rm *.gch;