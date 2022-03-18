/*
 * led_driver.h
 *
 * Created: 2022-02-18 12:42:55 PM
 *  Author: pente
 */ 

#include <avr/io.h>

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_


void init_leds();
void set_led(uint8_t led_no, uint8_t state);
void lightbar(uint8_t level);


#endif /* LED_DRIVER_H_ */