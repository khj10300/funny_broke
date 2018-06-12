#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <wiringPi.h>
#include <softPwm.h> 
#include <pigpiod_if2.h>

typedef enum {false, true} bool; 

#define RIGHT_SERVO 29
#define LEFT_SERVO 28
#define FRONT_SERVO 27
#define BACK_SERVO 26

int servoMove(int);
void* servoThreadRun (void *);
void init_servo_thread();

bool servoThreadFlag;
int servoOption;

/*** CDS SENSOR ***/

int read_mcp3408_adc(unsigned char adcChannel);
void calaulate_score(void);
void cds_sensor(void);
void* cdsThreadRun(void *data);
void* calculateThreadRun(void *data);
void init_cds_thread(void);

/*** LED BAR ***/
void ledbar_time(void);
void *ledThreadRun(void *data);
void init_ledbar_thread(void);
