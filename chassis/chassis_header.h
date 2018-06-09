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


#define FULLPWM 4096

#define PWMVAL 3000
#define rPWMVAL 2800 
#define lPWMVAL 2700 

void moveBack (int);
void moveStop (int);
void backTurnL (int, float);
void turnL (int, float);
void backTurnR(int, float);
void turnR(int,float);
void goForward(int);
void goBackward(int);
int setPwm(int, int, int);
void resetPwm(int);
void getItem_1(int);
void getItem_2(int);
void getItem_3(int);

void backFrom_1(int);
void backFrom_2(int);
void backFrom_3(int);

int ChassisMove(int);
void* ChassisThreadRun (void *);
void init_chassis_thread();

bool chassisThreadFlag;
unsigned char chassisOption;