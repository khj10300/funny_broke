#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <wiringPi.h>
#include <softPwm.h> 
#include <pigpiod_if2.h>
#include <stdbool>

#define RIGHT_SERVO 29
#define LEFT_SERVO 28
#define FRONT_SERVO 27
#define BACK_SERVO 26
int servoMove(int);
void* servoThreadRun (void *);
void init_servo_thread();

bool servoThreadFlag;
int servoOption;
