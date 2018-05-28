#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pigpiod_if2.h>
#include "7seg_functions.h"
#include <wiringPi.h>
#include <time.h>
#include <wiringPiSPI.h>

#define CS_MCP3208  6        // BCM_GPIO 25 
#define LED 1
#define SPI_CHANNEL 0
#define SPI_SPEED   1000000  // 1MHz

#define DIGIT1 23
#define DIGIT2 24

#define CDS0 0
#define CDS1 1

#define DARK 4000

uint8_t arr[] = {
     (uint8_t)~0b11111100, //0
     (uint8_t)~0b01100000, //1
     (uint8_t)~0b11011010, //2
     (uint8_t)~0b11110010, //3
     (uint8_t)~0b01100110, //4
     (uint8_t)~0b10110110, //5
     (uint8_t)~0b00111110, //6
     (uint8_t)~0b11100100, //7
     (uint8_t)~0b11111110, //8
     (uint8_t)~0b11100110 //9
};

int score, pi;

int read_mcp3208_adc(unsigned char adcChannel)
{

      unsigned char buff[3];
      int adcValue = 0;   

      buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
      buff[1] = ((adcChannel & 0x07) << 6);
      buff[2] = 0x00;
      
      digitalWrite(CS_MCP3208, 0);  // Low : CS Active
      wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);
      buff[1] = 0x0F & buff[1];
      adcValue = ( buff[1] << 8) | buff[2];
      digitalWrite(CS_MCP3208, 1);  // High : CS Inactive
      return adcValue;
} 

void *calculate_score(void *data)
{

    while(1){
        if(score >= 10){
            set8(arr[score/10]);
            gpio_write(pi, DIGIT2, PI_LOW); gpio_write(pi, DIGIT1, PI_HIGH);
            time_sleep(0.001);
            set8(arr[score % 10]);
            gpio_write(pi, DIGIT1, PI_LOW); gpio_write(pi, DIGIT2, PI_HIGH);
            time_sleep(0.001);
        }
      else{
          set8(arr[0]);  
          gpio_write(pi, DIGIT2, PI_LOW); gpio_write(pi, DIGIT1, PI_HIGH);
          time_sleep(0.001);
          set8(arr[score % 10]);
          gpio_write(pi, DIGIT1, PI_LOW); gpio_write(pi, DIGIT2, PI_HIGH);
          time_sleep(0.001);
      }
    }
}

int main (void)
{
    int adcChannel = 0;
    int adcChannel_1 = 1;

    int adcValue   = 0;
    int adcValue_1 =0;

    float adcVol   = 0;
    float adcVol_1 = 0;
    
    int ret;
    int res;

    ret = init();

    if(ret == 0)
        return 0;


    char t[] = "score";

    pthread_t score_thread;

    void *scorethread_result;

    int status;

    res = pthread_create(&score_thread, NULL, calculate_score, (void *) t);

    if(res < 0)
    {
        perror("thread create error\n");
        exit(0);
    }

    set_mode(pi, DIGIT1, PI_OUTPUT);
    set_mode(pi, DIGIT2, PI_OUTPUT);

    if(wiringPiSetup() == -1)
    {
        fprintf (stdout, "Unable to start wiringPi: %s\n", strerror(errno));
        return 1 ;
    }

    if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)                    
    {
        fprintf (stdout, "wiringPiSPISetup Failed: %s\n", strerror(errno));
        return 1 ;
    }
    
    pinMode(CS_MCP3208, OUTPUT);
    pinMode(LED, OUTPUT);

    int digit1, digit2;
    int cnt=0, cnt2=0;
    int check;

    uint32_t rateTimer;
    uint32_t now, controlPeriod = 2000;

    time_t start, end;
    struct tm *tmp;
    float gap;


    for(int i=0; ;i++)
    {
        adcValue = read_mcp3208_adc(adcChannel);
        adcValue_1 = read_mcp3208_adc(adcChannel_1);
        adcVol = (adcValue/4096.0)*3.3; 
        adcVol_1 = (adcValue_1 / 4096.0) * 3.3;

        start = clock();

        if(adcValue < DARK && check != CDS0){

            while(1){

                sleep(3);

                if(adcValue < DARK){
            //        printf("yes\n");
                    check = CDS0;
                    score ++;
                    break;
                }
            }

        }
        else if(adcValue_1 < DARK && check != CDS1){

            while(1){

                sleep(3);

                if(adcValue_1 < DARK){
              //      printf("yes2\n");
                    check = CDS1;
                    score +=2;
                    break;
                }
            }
        }

    }

    release();

    return 0;
}
