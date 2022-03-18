/*
 * Analog thermometer TMP36GRTZ.c
 *
 * Created: 2022-03-18 7:51:30 AM
 * Author : pente
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "drivers/key_driver.h"
#include "drivers/led_driver.h"
#include "drivers/TMP36GRTZ.h"


void thermometer_handler(uint16_t result);


volatile uint16_t temp;
volatile uint16_t count; 

int main(void)
{
	
    init_keys();
    init_leds();
    init_termometer(thermometer_handler);
    

    while (1) 
    {
        if (temp < 18) {
            lightbar(0);
        }
        if (temp > 18 && temp < 25) {
            lightbar(temp-17);
        }
        if (temp > 25) {
            lightbar(8);
        }
    }
}

void thermometer_handler(uint16_t result)
{
    temp = result;
}
