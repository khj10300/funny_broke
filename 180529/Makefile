servo_server.out : test_server.c test_header.h wiring_servo.c cds_sensor.c 7seg_functions.c 7seg_functions.h
	gcc -lrt -lpthread -lpigpiod_if2 -lwiringPi test_server.c \
		-o servo_server.out wiring_servo.c cds_sensor.c 7seg_functions.c
