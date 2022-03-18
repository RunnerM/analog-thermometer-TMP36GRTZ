/*
 * TMP36GRTZ.c
 *
 * Created: 2022-03-18 8:27:46 AM
 *  Author: pente
 */ 

#include "TMP36GRTZ.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static void (*cb)() = 0;
void init_timer();
void init_adc();

int sample;

void init_termometer(void (*call_back)()){
	init_adc();
	init_timer();
}


void init_timer() {
	TCCR4A = 0;// set entire TCCR4A register to 0
	TCCR4B = 0;// same for TCCR4B
	TCNT4 = 0;//initialize counter value to 0
	// set compare match register for 1hz increments
	OCR4A = 15624 / 1;// = (16*10^6) / (1*1024) - 1 (must be <65536)
	// turn on CTC mode
	TCCR4B |= (1 << WGM42);
	// Set CS12 and CS10 bits for 1024 prescaler
	TCCR4B |= (1 << CS42) | (1 << CS40);
	// enable timer compare interrupt
	TIMSK4 |= (1 << OCIE4A);
}

void init_adc(){
	//Set up input input
	DDRK &= ~_BV(PK7);
	//ADC set upt to chanel 15
	ADMUX |= _BV(REFS0) | _BV(MUX0) | _BV(MUX1) | _BV(MUX2);
	ADCSRB |= _BV(MUX2);
	//Enable ADC: Div fact:128, interupt enabled, free run...
	ADCSRA |= _BV(ADEN) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
}

ISR(ADC_vect) {
	//cache conversion result in sample 
	sample = ADC;
	//convert voltage to temp


	//call the callback function with the result
	cb();
}

ISR(TIMER4_COMPA_vect) {
	//start measuring on timer interrupt.
	ADCSRA |= _BV(ADSC);
}

