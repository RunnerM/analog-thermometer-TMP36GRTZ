/*
 * TMP36GRTZ.h
 *
 * Created: 2022-03-18 8:27:14 AM
 *  Author: pente
 */ 
#include <avr/io.h>

#ifndef TMP36GRTZ_H_
#define TMP36GRTZ_H_

void init_termometer(void (*call_back)(float result));
float calculate_temp(uint16_t sample);



#endif /* TMP36GRTZ_H_ */