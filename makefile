#Now the actual stuff
#needs libmysql++-dev to make
Sunday : sunday.o command.o controller.o main.o
		g++ main.o command.o sunday.o controller.o -o Sunday -lboost_regex-mt -lboost_thread-mt -I/usr/include/mysql -I/usr/include/mysql++/ -I/usr/local/include/mysql++/ -lmysqlpp -lmysqlclient

main.o: main.cpp
		g++ -Wall -Wextra -DDEBUG -c main.cpp 

sunday.o : sunday.cpp sunday.h command.o controller.o 
		g++ -Wall -Wextra -DDEBUG -c sunday.h sunday.cpp 

command.o : command.h command.cpp controller.h
		g++ -Wall -Wextra -DDEBUG -c command.h command.cpp -I/usr/include/mysql -I/usr/include/mysql++/ -I/usr/local/include/mysql++/ -lmysqlpp -lmysqlclient

controller.o : controller.h controller.cpp
		g++ -Wall -DDEBUG -Wextra -c controller.h controller.cpp -I/usr/include/mysql -I/usr/include/mysql++/ -I/usr/local/include/mysql++/ -lmysqlpp -lmysqlclient 

clean:
		rm -f Sunday

realclean:
		rm -f Sunday *.h.* *.o

