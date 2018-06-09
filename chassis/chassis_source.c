#include "chassis_header.h"

#include <wiringPi.h>
#include <softPwm.h>

#define PWM_LOW 0 
#define R_PWM_HIGH 65
#define L_PWM_HIGH 75

void
backTurnL(float sleepTime)
{
	softPwmWrite (IN1, R_PWM_HIGH );
	softPwmWrite (IN2, PWM_LOW);
	
	time_sleep(sleepTime);

	softPwmWrite (IN1, PWM_LOW);
}
void
turnL(float sleepTime)
{
	softPwmWrite (IN1, PWM_LOW);
	softPwmWrite (IN2, R_PWM_HIGH);
	
	time_sleep(sleepTime);

	softPwmWrite (IN2, PWM_LOW);
}

void
backTurnR(float sleepTime)
{
 	softPwmWrite (IN3, L_PWM_HIGH);
	softPwmWrite (IN4, PWM_LOW);

	time_sleep(sleepTime);

	softPwmWrite (IN3, PWM_LOW);
}
void
turnR(float sleepTime)
{
 	softPwmWrite (IN3, PWM_LOW);
	softPwmWrite (IN4, L_PWM_HIGH);

	time_sleep(sleepTime);

	softPwmWrite (IN4, PWM_LOW);
}

void 
goForward()
{	
	softPwmWrite (IN3, PWM_LOW);
	softPwmWrite (IN4, L_PWM_HIGH);
	softPwmWrite (IN1, PWM_LOW);
	softPwmWrite (IN2, R_PWM_HIGH);

	time_sleep(1);

	softPwmWrite (IN2, PWM_LOW);
	softPwmWrite (IN4, PWM_LOW);
}
void 
goBackward()
{
	softPwmWrite (IN1, R_PWM_HIGH);
	softPwmWrite (IN2, PWM_LOW);
	softPwmWrite (IN3, L_PWM_HIGH);
	softPwmWrite (IN4, PWM_LOW);

	time_sleep(1);

	softPwmWrite (IN1, PWM_LOW);
	softPwmWrite (IN3, PWM_LOW);
}

void
getItem_1()
{
    turnR (0.6);
    goForward ();
    turnL (0.8);
    goForward ();
}

void
getItem_2()
{
    for (int i=0; i<3;i++) 
        goForward ();
}

void
getItem_3()
{
    turnL (0.6);
    goForward ();
    turnR (0.6);
    goForward ();
}

void
backFrom_1()
{
    goBackward ();
    turnL (0.8);
    goForward ();
    goForward ();
    backTurnL (0.8); 
    goBackward ();
    goBackward ();
}

void 
backFrom_2()
{
    for (int i=0; i<3;i++) 
        goBackward ();
}

void 
backFrom_3()
{
    goBackward ();
    turnR (0.8);
    goForward ();
    goForward ();
    backTurnR (0.5); 
    goBackward ();
    goBackward ();
    
}

int 
main ()
{
	if(wiringPiSetup()==-1)
        return -1;
    softPwmCreate (IN1, 0, 100);
    softPwmCreate (IN2, 0, 100);
    softPwmCreate (IN3, 0, 100);
    softPwmCreate (IN4, 0, 100);

	int op;

	while (1)
	{
		printf ("op : ");
		scanf ("%d", &op);
		getchar();
		switch (op)
    	{
      	 	case 1: getItem_1(); break;
       		case 2: getItem_2(); break;
      		case 3: getItem_3(); break;
        
     	    case 4: backFrom_1(); break;
       	    case 5: backFrom_2(); break;
       		case 6: backFrom_3(); break;
         	default : return 0;       
    	}
	} 
}

/*
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
*/
