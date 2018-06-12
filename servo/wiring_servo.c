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

int pi; 
void InitPigpiod ();
int ServoMovePigpiod(int gpio, int degree);


int servoMove(int op)
{
    if(wiringPiSetup()==-1)
        return -1;
    softPwmCreate(RIGHT_SERVO, 0, 200);
    softPwmCreate(LEFT_SERVO, 0, 200);
    softPwmCreate(FRONT_SERVO, 0, 200);
    softPwmCreate(BACK_SERVO, 0, 200);

    switch (op)
    {
        case 1:
                softPwmWrite(BACK_SERVO, 0); 
                time_sleep(1);
                softPwmWrite(FRONT_SERVO, 10);
                break; // upwards moving.  
        case 2:
                softPwmWrite(BACK_SERVO, 24); 
                softPwmWrite(FRONT_SERVO, 16); time_sleep(1); 
                break; // downward moving.  
        case 3: 
                softPwmWrite(RIGHT_SERVO, 8); time_sleep(1);
                softPwmWrite(LEFT_SERVO,12);
                break; // leftward moving.  
        case 4:
                softPwmWrite(LEFT_SERVO, 48); time_sleep(1);
                softPwmWrite(RIGHT_SERVO, 16); 
                break; // rightward moving.            
    }
    return 1;
}



int main()
{
    for (;;)
    {
     int op;
     scanf ("%d", &op);
     printf ("option : %d\n", op);
     servoMove(op);
     memset (&op, 0, sizeof(int));
    }
    
    return 0;
}

void* servoThreadRun (void *data)
{
    if(wiringPiSetup()==-1)
        return -1;
    softPwmCreate(RIGHT_SERVO, 0, 200);
    softPwmCreate(LEFT_SERVO, 0, 200);
    softPwmCreate(FRONT_SERVO, 0, 200);
    softPwmCreate(BACK_SERVO, 0, 200);
    
    servoThreadFlag = false;
    while (1) 
    {
        if (servoThreadFlag == true)
        {
            printf ("%d\n", servoOption);
            if (servoMove(servoOption)==-1)
            {
                fprintf (stderr, "option number : %d servo thread end\n",servoOption);
                break;
            }
            servoThreadFlag = false;
            servoOption = 0;
        }
    }
}

void init_servo_thread()
{
    pthread_t servo_thread_id;
    int status;

    if (pthread_create (&servo_thread_id, NULL, servoThreadRun, NULL) < 0)
    {
        fprintf (stderr, "servo pthread_create error\n");
        exit(-1);
    }
}

int ServoMovePigpiod(int gpio, int degree) 
{ 
    int pulse_width; 
   
    
    if(degree >= 0 && degree <= 180)
    { 
        pulse_width = (degree * 11.11111) + 500; 
        set_servo_pulsewidth(pi, gpio, pulse_width); 
        printf("degree: %d\n", degree); 
    } 
    return 0; 
}

void
InitPigpiod ()
{
    if((pi = pigpio_start(NULL, NULL)) < 0)
    { 
        fprintf(stderr, "pigpio_start error\n"); 
        return 1; 
    }
    set_mode(pi, RIGHT_SERVO, PI_OUTPUT);  
    set_mode(pi, LEFT_SERVO, PI_OUTPUT); 
    set_mode(pi, FRONT_SERVO, PI_OUTPUT); 
    set_mode(pi, BACK_SERVO, PI_OUTPUT); 

}

