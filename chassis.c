#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pigpiod_if2.h>
#include <unistd.h>
 
#define GPIO19 19  //IN1 
#define GPIO13 13 //IN2 13
#define GPIO5 5	 //IN3 5
#define GPIO6 6 //IN4

#define PWMVAL 2600
#define FULLPWM 4096

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

int chassisMain(int);

int 
main(int argc char* argv[])
{
	int i;
	int pi;
	if ((pi = pigpio_start(NULL, NULL)) < 0)
	{
		fprintf (stderr, "%s\n", pigpio_error(pi));
		exit(-1);
	}
	set_mode(pi, GPIO5, PI_OUTPUT);
	set_mode(pi, GPIO6, PI_OUTPUT);
	set_mode(pi, GPIO13, PI_OUTPUT);
	set_mode(pi, GPIO19, PI_OUTPUT);

	moveBack(pi);
    switch (moveOption)
    {
        case 1: getItem_1(pi); break;
        case 2: getItem_2(pi); break;
        case 3: getItem_3(pi); break;
        
        case 4: backFrom_1(pi); break;
        case 5: backFrom_2(pi); break;
        case 6: backFrom_3(pi); break;
                
    }

	gpio_write (pi, GPIO5, PI_LOW);
	gpio_write (pi, GPIO6, PI_LOW);
	gpio_write (pi, GPIO13, PI_LOW);
	gpio_write (pi, GPIO19, PI_LOW);

	pigpio_stop(pi);

	return 0;
}

void
moveStop(int pi)
{
	gpio_write (pi, GPIO5, PI_LOW);
	gpio_write (pi, GPIO6, PI_LOW);
	gpio_write (pi, GPIO13, PI_LOW);
	gpio_write (pi, GPIO19, PI_LOW);
    time_sleep(1);
}
void 
moveBack(int pi)
{
	gpio_write(pi, GPIO19, PI_HIGH);
	gpio_write(pi, GPIO13, PI_LOW);
	gpio_write(pi, GPIO6, PI_LOW);
	gpio_write(pi, GPIO5, PI_HIGH);
	time_sleep(1);
	gpio_wirte(pi, GPIO19, PI_LOW);
	gpio_write(pi, GPIO5, PI_LOW);
}

void
backTurnL(int pi, float sleepTime)
{
	gpio_write(pi, GPIO19, PI_HIGH);
	gpio_write(pi, GPIO13, PI_LOW);
	setPwm(pi, PWMVAL, 3);
	time_sleep(sleepTime);
    resetPwm(pi);
	gpio_write(pi, GPIO19, PI_LOW);
}
void
turnL(int pi, float sleepTime)
{
	gpio_write(pi, GPIO19, PI_LOW);
	gpio_write(pi, GPIO13, PI_HIGH);
	setPwm(pi, PWMVAL, 3);
	time_sleep(sleepTime);
    resetPwm(pi);
	gpio_write(pi, GPIO19, PI_LOW);
}

void
backTurnR(int pi, float sleepTime)
{
	gpio_write(pi, GPIO5, PI_HIGH);
	gpio_write(pi, GPIO6, PI_LOW);
	setPwm(pi, PWMVAL, 2);
	time_sleep(sleepTime);
    resetPwm(pi);
	gpio_write(pi, GPIO5, PI_LOW);
}
void
turnR(int pi, float sleepTime)
{
	gpio_write(pi, GPIO5, PI_LOW);
	gpio_write(pi, GPIO6, PI_HIGH);
	setPwm(pi, PWMVAL, 2);
	time_sleep(sleepTime);
    resetPwm(pi);
	gpio_write(pi, GPIO6, PI_LOW);
}

void 
goForward(int pi)
{
	gpio_write(pi, GPIO19, PI_LOW);
	gpio_write(pi, GPIO13, PI_HIGH);
	gpio_write(pi, GPIO6, PI_HIGH);
	gpio_write(pi, GPIO5, PI_LOW);
	setPwm(pi, PWMVAL, 0);
	time_sleep(0.7);
    resetPwm(pi);
	gpio_write(pi, GPIO19, PI_LOW);
	gpio_write(pi, GPIO5, PI_LOW);
}
void 
goBackward(int pi)
{
	gpio_write(pi, GPIO19, PI_HIGH);
	gpio_write(pi, GPIO13, PI_LOW);
	gpio_write(pi, GPIO6, PI_LOW);
	gpio_write(pi, GPIO5, PI_HIGH);
	setPwm(pi, PWMVAL, 1);
	time_sleep(0.8);
    resetPwm(pi);
	gpio_write(pi, GPIO13, PI_LOW);
	gpio_write(pi, GPIO6, PI_LOW);
}

int
setPwm(int pi, int val, int op)
{
    return 0;
	int range;
	int default_range = 4096;

	set_PWM_range(pi, GPIO5, default_range);
	set_PWM_range(pi, GPIO6, default_range);
	set_PWM_range(pi, GPIO13, default_range);
	set_PWM_range(pi, GPIO19, default_range);

	// gofoward(0) goBackward(1) turnR(2) turnL(3) 
	switch (op)
	{
		case 0:	set_PWM_dutycycle(pi, GPIO6, val); set_PWM_dutycycle(pi, GPIO19, val);
				break;
		case 1:	set_PWM_dutycycle(pi, GPIO5, val); set_PWM_dutycycle(pi, GPIO13, val);
				break;
		case 2: set_PWM_dutycycle(pi, GPIO6, val); 
				break;
		case 3: set_PWM_dutycycle(pi, GPIO19, val);
				break;
	}

/*
	range = get_PWM_range(pi, IN2);
	printf ("range : %d\n", range);
	int duty = get_PWM_dutycycle(pi, IN1);
	printf("duty cycle:%.1f%% %d/%d\n", DUTYCYCLE(duty,range), i, range);
*/


/*
	set_PWM_dutycycle (pi, IN1, 0);
	set_PWM_dutycycle (pi, IN2, 0);
	set_PWM_dutycycle (pi, IN3, 0);
	set_PWM_dutycycle (pi, IN4, 0);
*/
	
	return 0;
}

void
resetPwm(int pi)
{
	int default_range = 4096;
	set_PWM_dutycycle (pi, GPIO5, 0);
	set_PWM_dutycycle (pi, GPIO6, 0);
	set_PWM_dutycycle (pi, GPIO13, 0);
	set_PWM_dutycycle (pi, GPIO19, 0);
}

void
getItem_1(int pi)
{
    turnR(pi, 0.6);
    goForward(pi);
    turnL(pi, 0.6);
    goForward(pi);
}

void
getItem_2(int pi)
{
    for (int i=0; i<3;i++) 
        goForward(pi);
}

void
getItem_3(int pi)
{
    turnL(pi, 0.6);
    goForward(pi);
    turnR(pi, 0.6);
    goForward(pi);
}

void
backFrom_1(int pi)
{
    goBackward(pi);
    turnL(pi, 1);
    goForward(pi);
    goForward(pi);
    backTurnL(pi, 1); 
    goBackward(pi);
    goBackward(pi);
}

void 
backFrom_2(int pi)
{
    for (int i=0; i<3;i++) 
        goBackward(pi);
}

void 
backFrom_3(int pi)
{
    goBackward(pi);
    turnR(pi, 1);
    goForward(pi);
    goForward(pi);
    backTurnR(pi, 0.8); 
    goBackward(pi);
    goBackward(pi);
    
}