#include "chassis_header.h"

#include <wiringPi.h>
#include <softPwm.h>

#define PWM_FULL 100
#define PWM_LOW 0 
#define PWM_HIGH 70
#define R_PWM_HIGH 62
#define L_PWM_HIGH 72

void
backTurnL(float sleepTime)
{
	softPwmWrite (IN1, PWM_HIGH);
	softPwmWrite (IN2, PWM_LOW);
	
	time_sleep(sleepTime);

	softPwmWrite (IN1, PWM_LOW);
}
void
turnL(float sleepTime)
{
	softPwmWrite (IN1, PWM_LOW);
	softPwmWrite (IN2, PWM_HIGH);
	
	time_sleep(sleepTime);

	softPwmWrite (IN2, PWM_LOW);
}

void
backTurnR(float sleepTime)
{
 	softPwmWrite (IN3, PWM_HIGH);
	softPwmWrite (IN4, PWM_LOW);

	time_sleep(sleepTime);

	softPwmWrite (IN3, PWM_LOW);
}
void
turnR(float sleepTime)
{
 	softPwmWrite (IN3, PWM_LOW);
	softPwmWrite (IN4, PWM_HIGH);

	time_sleep(sleepTime);

	softPwmWrite (IN4, PWM_LOW);
}

void 
goForward(float sleepTime)
{	
	softPwmWrite (IN3, PWM_LOW);
	softPwmWrite (IN4, L_PWM_HIGH);
	softPwmWrite (IN1, PWM_LOW);
	softPwmWrite (IN2, R_PWM_HIGH);

	time_sleep(1);

    time_sleep (sleepTime);

	softPwmWrite (IN2, PWM_LOW);
	softPwmWrite (IN4, PWM_LOW);
}
void 
goBackward(int rval, int lval, float sleepTime)
{
	softPwmWrite (IN1, rval);
	softPwmWrite (IN2, PWM_LOW);
	softPwmWrite (IN3, lval);
	softPwmWrite (IN4, PWM_LOW);

	time_sleep(1);
     
    time_sleep (sleepTime);

	softPwmWrite (IN1, PWM_LOW);
	softPwmWrite (IN3, PWM_LOW);
}

void
getItem_1()
{
    turnR (0.6);
    goForward (0.0);
    turnL (0.3);
    goForward (0.0);
}

void
getItem_2()
{
    for (int i=0; i<3;i++) 
       goForward (0.0);
}

void
getItem_3()
{
    turnL (0.6);
    goForward (0.0);
    turnR (0.7);
    goForward (0.0);
}

void
backFrom_1()
{
    goBackward (70,70, 0.0);
    turnL (0.6);
    goForward (0.6);
    backTurnL (0.3); 
    goBackward (80,90, 1.0);
}

void 
backFrom_2()
{
    goBackward (PWM_FULL-10, PWM_FULL, 1.5);
}

void 
backFrom_3()
{
    goBackward (70,70, 0.0);
    turnR (0.6);
    goForward (0.6);
    backTurnR (0.7); 
    goBackward (80,90, 0.5);
}

int 
ChassisMove()
{
	int i;

	printf ("chassisOption: %d", chassisOption);

   	switch (chassisOption)
    {
      	 	case 1: 
      	 			getItem_1 (); 
      	 			time_sleep (1);
      	 			backFrom_1 ();
      	 			break;
       		case 2: 
       				getItem_2 (); 
      	 			time_sleep (1);
      	 			backFrom_2 ();
      	 			break;
      		case 3: 
      				getItem_3 (); 
      	 			time_sleep (1);
      	 			backFrom_3 ();
      	 			break;
         	default : return 0;       
    }


	return 0;
}


void* 
ChassisThreadRun (void *data)
{
	chassisThreadFlag = false;
	while (1)
	{
		if (chassisThreadFlag == true)
		{
			printf ("chassis option : %d\n", chassisOption);

			if (ChassisMove()==-1)
			{
				fprintf (stderr, "ChassisMove() error for %d\n", chassisOption);
			}
			chassisThreadFlag = false;
			chassisOption = 0;
		}
	}
}

void 
init_chassis_thread()
{
	pthread_t chassis_tid=0;
	int status=0;
	
	if(wiringPiSetup()==-1)
        return;
    softPwmCreate (IN1, 0, 100);
    softPwmCreate (IN2, 0, 100);
    softPwmCreate (IN3, 0, 100);
    softPwmCreate (IN4, 0, 100);

	if (pthread_create (&chassis_tid, NULL, ChassisThreadRun, NULL)<0)
	{
		fprintf (stderr, "chassis pthread_create error\n");
		exit(-1);
	}
}

