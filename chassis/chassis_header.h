#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pigpiod_if2.h>
#include <unistd.h>
 
#define IN1 24 // GPIO19 
#define IN2 23 // GPIO13
#define IN3 21 // GPIO5
#define IN4 22 // GPIO6

void backTurnL (float);
void turnL (float);
void backTurnR(float);
void turnR(float);

void goForward (float);
void goBackward (int,int, float);

void getItem_1();
void getItem_2();
void getItem_3();

int ChassisMove();
void* ChassisThreadRun (void *);
void init_chassis_thread();

bool chassisThreadFlag;
unsigned char chassisOption;
