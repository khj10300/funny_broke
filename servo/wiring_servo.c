#include "test_header.h"

int front_speed = 7;
int back_speed = 7;

int servoMove(int op)
{
    if (!(op == 1 || op == 2 || op == 3 || op == 4))
    {
        fprintf (stderr, "invalid option number taek either 1 or 2\n");
        return -1;
    }

     if(wiringPiSetup()==-1)
        return -1;
    softPwmCreate(RIGHT_SERVO, 0, 200);
    softPwmCreate(LEFT_SERVO, 0, 200);
    softPwmCreate(FRONT_SERVO, 0, 200);
    softPwmCreate(BACK_SERVO, 0, 200);

    switch (op)
    {
        case 1: 
              //softPwmWrite(BACK_SERVO, 7);  time_sleep(1);
                softPwmWrite(FRONT_SERVO,10); 
                break; // upwards moving.  
        case 2: 
                softPwmWrite(FRONT_SERVO, 16);  time_sleep(1); 
                //softPwmWrite(BACK_SERVO, back_speed); 
                time_sleep(1); 
                break; // downward moving.  
        case 3:
                softPwmWrite(RIGHT_SERVO, 8); //time_sleep(1);
                //softPwmWrite(LEFT_SERVO, 48);
                time_sleep(1); 
                break; // leftward moving.  
        case 4: 
             //   softPwmWrite(LEFT_SERVO, 24); time_sleep(1);
                softPwmWrite(RIGHT_SERVO, 16);
                time_sleep(1); 
                break; // rightward moving.            
    }
    return 1;
}

void* servoThreadRun (void *data)
{
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

