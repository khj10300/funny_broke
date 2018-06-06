#include "chassis_header.h"
int pi;


void
moveStop(int pi)
{
	gpio_write (pi, GPIO5, PI_LOW);
	gpio_write (pi, GPIO6, PI_LOW);
	gpio_write (pi, GPIO13, PI_LOW);
	gpio_write (pi, GPIO19, PI_LOW);
    time_sleep(1.2);
}
void 
moveBack(int pi)
{
	gpio_write(pi, GPIO19, PI_HIGH);
	gpio_write(pi, GPIO13, PI_LOW);
	gpio_write(pi, GPIO6, PI_LOW);
	gpio_write(pi, GPIO5, PI_HIGH);
	time_sleep(1.2);
	gpio_write(pi, GPIO19, PI_LOW);
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
	time_sleep(0.8);
    resetPwm(pi);
	gpio_write(pi, GPIO13, PI_LOW);
	gpio_write(pi, GPIO6, PI_LOW);
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
	int range;
	int default_range = 4096;

	set_PWM_range(pi, GPIO5, default_range);
	set_PWM_range(pi, GPIO6, default_range);
	set_PWM_range(pi, GPIO13, default_range);
	set_PWM_range(pi, GPIO19, default_range);

	// gofoward(0) goBackward(1) turnR(2) turnL(3) 
	switch (op)
	{
		case 0:	set_PWM_dutycycle(pi, GPIO6, val); set_PWM_dutycycle(pi, GPIO13, val);
				break;
		case 1:	set_PWM_dutycycle(pi, GPIO5, val); set_PWM_dutycycle(pi, GPIO13, val);
				break;
		case 2: set_PWM_dutycycle(pi, GPIO6, val); 
				break;
		case 3: set_PWM_dutycycle(pi, GPIO19, val);
				break;
	}
	
	return 0;
}

void
resetPwm(int pi)
{
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
    turnL(pi, 0.8);
    goForward(pi);
    goForward(pi);
    backTurnL(pi, 0.8); 
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
    turnR(pi, 0.8);
    goForward(pi);
    goForward(pi);
    backTurnR(pi, 0.5); 
    goBackward(pi);
    goBackward(pi);
    
}

int 
ChassisMove(int pi)
{
	int i;

	printf ("pi: %d, chassisOption: %d", pi, chassisOption);

    moveBack(pi);
    switch (chassisOption)
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


	return 0;
}


void* 
ChassisThreadRun (void *data)
{
	printf ("ChassisThreadRun_pi : %d\n", pi);
	chassisThreadFlag = false;
	while (1)
	{
		if (chassisThreadFlag == true)
		{
			printf ("chassis option : %d\n", chassisOption);
			if (ChassisMove(pi)==-1)
			{
				fprintf (stderr, "ChassisMove() error for %d\n", chassisOption);
			}
			chassisThreadFlag = false;
			chassisOption = 0;
		}
	}
	pigpio_stop(pi);
}

void 
init_chassis_thread()
{
	pthread_t chassis_tid=0;
	int status=0;
	
	if ((pi = pigpio_start(NULL, NULL)) < 0)
	{
		fprintf (stderr, "%s\n", pigpio_error(pi));
		exit(-1);
	}

	set_mode(pi, GPIO5, PI_OUTPUT);
	set_mode(pi, GPIO6, PI_OUTPUT);
	set_mode(pi, GPIO13, PI_OUTPUT);
	set_mode(pi, GPIO19, PI_OUTPUT);
	if (pthread_create (&chassis_tid, NULL, ChassisThreadRun, (void*)&pi)<0)
	{
		fprintf (stderr, "chassis pthread_create error\n");
		exit(-1);
	}
}
