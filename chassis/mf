chassis.out : test_server.c chassis_source.o chassis_header.h 
	gcc -W -Wall -lrt -pthread -lpigpiod_if2 test_server.c chassis_source.o \
													-o chassis.out
chassis_source.o : chassis_source.c chassis_header.h
	gcc -W -Wall -lrt -pthread -lpigpiod_if2 -c chassis_source.c 