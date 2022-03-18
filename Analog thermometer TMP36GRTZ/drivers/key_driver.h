/*
 * key_driver.h
 *
 * Created: 2022-02-18 1:28:50 PM
 *  Author: pente
 */ 

#include <avr/io.h>

#ifndef KEY_DRIVER_H_
#define KEY_DRIVER_H_

void init_keys();
uint8_t get_key(uint8_t key_no);
uint8_t scan_key();



#endif /* KEY_DRIVER_H_ */