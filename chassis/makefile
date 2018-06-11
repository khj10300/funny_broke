test.out : chassis_source.o chassis_header.h
	gcc -lrt -lpthread -lpigpiod_if2 -lwiringPi test_server.c chassis_source.c -o test.out 
chassis_source.o : chassis_source.c chassis_header.h
	gcc -lrt -lpthread -lpigpiod_if2 -lwiringPi -c chassis_source.c 
