#include "test_header.h"

#define SDATA_LED 2
#define STR_CLK_LED     3   // Storage Register Clock(LATCH)
#define SHR_CLK_LED     4   // Shift Register Clock
#define SHR_CLEAR_LED   17   // Shift Register Clear

void allclear_led(void);
int init_led(void);
void release_led(void);
void set_led(int index);
void set8_led(uint8_t index);
void set16_led(uint16_t index);

