/*
 * led_driver.c
 *
 * Created: 2022-02-18 12:43:13 PM
 *  Author: pente
 */ 
#include "led_driver.h"

void init_leds() {
	DDRA = 0xFF;
	PORTA = 0xFF;
}
void set_led(uint8_t led_no, uint8_t state)
{
	led_no--;
	if (state==0)
	{
		PORTA |= 1 << led_no;
	}else{
		PORTA &= ~(1<<led_no);
	}
}

void lightbar(uint8_t level)
{
	PORTA = 0xFF; //turning off every led for housekeeping reasons.
	//turning on all the leds according to level.
	if (level>8) {
		level = 8; //making sure level is in range so no overflow will be experienced.
	}
	for (int i = 0; i <= level; i++) {
		set_led(i,1);
	}
}
