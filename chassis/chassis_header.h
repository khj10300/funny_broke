#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pigpiod_if2.h>
#include <unistd.h>
 
#define GPIO19 19  //IN1 
#define GPIO13 13 //IN2 13
#define GPIO5 5	 //IN3 5
#define GPIO6 6 //IN4


#define FULLPWM 4096

#define PWMVAL 2600
#define rPWMVAL 2500 
#define lPWMVAL 2600 

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