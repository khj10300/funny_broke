#include <time.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "7seg_functions.h"
#include <wiringPiSPI.h>

#define CS_MCP3208  6        // BCM_GPIO 25 
#define LED 1
#define SPI_CHANNEL 0
#define SPI_SPEED   1000000  // 1MHz

#define DIGIT1 23
#define DIGIT2 24

#define CDS0 0
#define CDS1 1
#define CDS2 2
#define CDS3 3
#define CDS4 4
#define CDS5 5
#define CDS6 6
#define CDS7 7

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
bool digitThreadFlag;

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

void calculate_score(void)
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

void cds_sensor(void)
{
    int adcChannel = 0;
    int adcChannel_1 = 1;
    int adcChannel_2 = 2;
    int adcChannel_3 = 3;
    int adcChannel_4 = 4;
    int adcChannel_5 = 5;
    int adcChannel_6 = 6;
    int adcChannel_7 = 7;

    int adcValue   = 0;
    int adcValue_1 =0;
    int adcValue_2 =0;
    int adcValue_3 =0;
    int adcValue_4 =0;
    int adcValue_5 =0;
    int adcValue_6 =0;
    int adcValue_7 =0;


    float adcVol   = 0;
    float adcVol_1 = 0;
    float adcVol_2 = 0;
    float adcVol_3 = 0;
    float adcVol_4 = 0;
    float adcVol_5 = 0;
    float adcVol_6 = 0;
    float adcVol_7 = 0;

    int check;
    time_t start, end;
    struct tm *tmp;
    float gap;


    if(wiringPiSetup() == -1)
    {
        fprintf(stdout, "Unable to start wiringPi : %s\n", strerror(errno));
        //return ;
    }

    if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)
    {
        fprintf(stdout, "wiringPiSPISetup Failed : %s\n", strerror(errno));
        //return ;
    }

    pinMode(CS_MCP3208, OUTPUT);
    pinMode(LED, OUTPUT);

    for(int i=0; ; i++)
    {
        adcValue = read_mcp3208_adc(adcChannel);
        adcValue_1 = read_mcp3208_adc(adcChannel_1);
        adcValue_2 = read_mcp3208_adc(adcChannel_2);
        adcValue_3 = read_mcp3208_adc(adcChannel_3);
        adcValue_4 = read_mcp3208_adc(adcChannel_4);
        adcValue_5 = read_mcp3208_adc(adcChannel_5);
        adcValue_6 = read_mcp3208_adc(adcChannel_6);
        adcValue_7 = read_mcp3208_adc(adcChannel_7);

        adcVol = (adcValue/4096.0)*3.3;
        adcVol_1 = (adcValue_1/4096.0)*3.3;

        start = clock();

        printf("1 : %d 2 : %d 3 : %d 4 : %d\n", adcValue, adcValue_1, adcValue_2, adcValue_3);
        printf("5 : %d 6 : %d 7 : %d 8 : %d\n", adcValue_4, adcValue_5, adcValue_6, adcValue_7);
        printf("\n");

        sleep(1);
        if(adcValue < DARK && check != CDS0){
            while(1){
               // calculate_score();
                sleep(3);

                if(adcValue < DARK){
                    printf("1\n");
                    check = CDS0;
                    score++;
                    break;
                }
            }
        }
        else if(adcValue_1 < DARK && check != CDS1){
            while(1){
               // calculate_score();
                sleep(3);
                if(adcValue_1 < DARK){
                    printf("2\n");
                    check = CDS1;
                    score += 2;
                    break;
                }
            }
        }
        else if(adcValue_2 < DARK && check != CDS2){
            while(1){
               // calculate_score();
                sleep(3);
                if(adcValue_2 < DARK){
                    printf("3\n");
                    check = CDS2;
                    score += 3;
                    break;
                }
            }
        }
        else if(adcValue_3 < DARK && check != CDS3){
            while(1){
               // calculate_score();
                sleep(3);
                if(adcValue_3 < DARK){
                    printf("4\n");
                    check = CDS3;
                    score += 4;
                    break;
                }
            }
        }
        else if(adcValue_4 < DARK && check != CDS4){
            while(1){
               // calculate_score();
                sleep(3);
                if(adcValue_4 < DARK){
                    printf("5\n");
                    check = CDS4;
                    score += 5;
                    break;
                }
            }
        }
        else if(adcValue_5 < DARK && check != CDS5){
            while(1){
               // calculate_score();
                sleep(3);
                if(adcValue_5 < DARK){
                    printf("6\n");
                    check = CDS5;
                    score += 6;
                    break;
                }
            }
        }
        else if(adcValue_6 < DARK && check != CDS6){
            while(1){
               // calculate_score();
                sleep(3);
                if(adcValue_6 < DARK){
                    printf("6\n");
                    check = CDS6;
                    score += 7;
                    break;
                }
            }
        }
        else if(adcValue_7 < DARK && check != CDS7){
            while(1){
               // calculate_score();
                sleep(3);
                if(adcValue_1 < DARK){
                    printf("7\n");
                    check = CDS7;
                    score += 8;
                    break;
                }
            }
        }
    }
}

void* cdsThreadRun(void *data)
{
    set_mode(pi, DIGIT2, PI_OUTPUT);
    set_mode(pi, DIGIT1, PI_OUTPUT);
    digitThreadFlag = false;
    while(1)
    {
        //printf("digit : %d\n", digitThreadFlag);
        if(digitThreadFlag == true){
            cds_sensor();
       //     digitThreadFlag = false;
        }
        //calculate_score();
        digitThreadFlag == false;
    }
}

void* calculateThreadRun(void *data)
{
    //digitThreadFlag = false;
    while(1){
        if(digitThreadFlag == true){
            calculate_score();
        //    digitThreadFlag = false;
        }
        digitThreadFlag == false;
    }
}

void init_cds_thread(void)
{
    int ret;
    int res, res1;

    ret = init();

    if(ret == 0)
        return ;


    char t[] = "score";

    pthread_t score_thread;
    pthread_t cds_thread;

    void *scorethread_result;

    int status;


    res1 = pthread_create(&score_thread, NULL, calculateThreadRun, (void *) t);
    res = pthread_create(&cds_thread, NULL, cdsThreadRun, (void *)t);


    if(res < 0)
    {
        perror("thread create error\n");
        exit(0);
    }

    return ;
}
