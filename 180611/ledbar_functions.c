#include "ledbar_functions.h" 

int pi;
int init_led(void)
{
    if((pi = pigpio_start(NULL, NULL)) < 0){
        fprintf(stderr, "%s\n", pigpio_error(pi));
        return 0;
    }
    
    set_mode(pi, SDATA_LED, PI_OUTPUT);
    set_mode(pi, STR_CLK_LED, PI_OUTPUT);
    set_mode(pi, SHR_CLK_LED, PI_OUTPUT);
    set_mode(pi, SHR_CLEAR_LED, PI_OUTPUT);
    gpio_write(pi, SHR_CLEAR_LED, 1);
    return 1;
}

void release_led(void)
{
    allclear_led();
    pigpio_stop(pi);
}

void allclear_led(void)
{
    gpio_write(pi, SHR_CLEAR_LED, 0);   gpio_write(pi, SHR_CLEAR_LED, 1); // clear
    gpio_write(pi, STR_CLK_LED, 0);     gpio_write(pi, STR_CLK_LED, 1);   // latch
}

void set_led(int index)
{
    gpio_write(pi, SDATA_LED, 1);
    gpio_write(pi, SHR_CLK_LED, 0);
    gpio_write(pi, SHR_CLK_LED, 1);
    gpio_write(pi, SDATA_LED, 0);

    for(int i = 0 ; i < index ; i++){
        gpio_write(pi, SHR_CLK_LED, 0);
        gpio_write(pi, SHR_CLK_LED, 1);   // shift
    }
    gpio_write(pi, STR_CLK_LED, 0);
    gpio_write(pi, STR_CLK_LED, 1);   // latch
}

// unsinged 8bit int
void set8_led(uint8_t value)
{
	for(int i = 0 ; i < 8 ; i++){
		int mask = 0b1 << i;
		if((value & mask) == 0)
			gpio_write(pi, SDATA_LED, 0);
		else
			gpio_write(pi, SDATA_LED, 1);
		gpio_write(pi, SHR_CLK_LED, 0); 
		gpio_write(pi, SHR_CLK_LED, 1); 
	}
	// letch
	gpio_write(pi, STR_CLK_LED, 0); 
	gpio_write(pi, STR_CLK_LED, 1);
}

void set16_led(uint16_t value)
{
    for(int i = 0 ; i < 16 ; i++){
        int mask = 0b1 << i;
        if((value & mask) == 0)
            gpio_write(pi, SDATA_LED, 0);
        else
            gpio_write(pi, SDATA_LED, 1);
        gpio_write(pi, SHR_CLK_LED, 0);
        gpio_write(pi, SHR_CLK_LED, 1);
    }
    // letch
    gpio_write(pi, STR_CLK_LED, 0);
    gpio_write(pi, STR_CLK_LED, 1);
}

