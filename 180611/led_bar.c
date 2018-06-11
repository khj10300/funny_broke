#include <stdio.h>
#include <pigpiod_if2.h>
#include "ledbar_functions.h"

void ledbar_time(void)
{
    int ret;
    uint16_t tmp;
    uint16_t arr[] = {  0b1111111111000000,
                        0b0111111111000000,
                        0b0011111111000000,
                        0b0001111111000000,
                        0b0000111111000000,
                        0b0000011111000000,
                        0b0000001111000000,
                        0b0000000111000000,
                        0b0000000011000000,
                        0b0000000001000000};

    ret = init_led();
    if(ret == 0)
        return ;

    for(int i = 0 ; i < 100 ; i++){
      //  tmp = (arr[i] << 10) | 0b000000;
        set16_led(arr[i]);
        time_sleep(6);
    }

    release_led();
    return ;
}

void *ledThreadRun(void *data)
{
    while(1)
        ledbar_time();
}

void init_ledbar_thread(void)
{
    int ret;
    int res;

    ret = init_led();

    if(ret == 0)
        return ;

    char t[] = "time";

    pthread_t led_thread;

    void *ledthread_result;

    int status;

    res = pthread_create(&led_thread, NULL, ledThreadRun, (void *)t);

    if(res < 0){
        perror("thread create error\n");
        exit(0);
    }

    return ;
}
