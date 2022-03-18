/*
 * TMP36GRTZ.c
 *
 * Created: 2022-03-18 8:27:46 AM
 *  Author: pente
 */ 

#include "TMP36GRTZ.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static void (*cb)(uint16_t result) = 0;
void init_timer();
void init_adc();

uint16_t sample;
uint16_t result;

void init_termometer(void (*call_back)(uint16_t result)){
	init_timer();
	init_adc();
	cb = call_back;
}


void init_timer() {
	cli();
	//Timer/Counter 1 is 16bit
	TCCR1A = 0;// set entire TCCR4A register to 0
	TCCR1B = 0;// same for TCCR4B
	TCNT1 = 0;//initialize counter value to 0
	// set compare match register for 1hz increments
	OCR1B = 15624 / 1;// = (16*10^6) / (1*1024) - 1 (must be <65536)
	// turn on CTC mode
	TCCR1B |= (1 << WGM12);
	// Set CS12 and CS10 bits for 1024 prescaler
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1B);
	sei();
}

void init_adc(){
	cli();
	//Set up input input
	DDRK &= ~_BV(PK7);
	//Set source for chip
	DDRK |= _BV(PG0);
	PORTA |= 1 << PG0;
	//ADC set upt to chanel 15  (100111)
	//ADMUX |=  _BV(MUX0) | _BV(MUX1) | _BV(MUX2);
	ADMUX |= _BV(REFS0) | _BV(MUX0) | _BV(MUX1) | _BV(MUX2);
	//ADMUX |= _BV(REFS1) | _BV(MUX0) | _BV(MUX1) | _BV(MUX2);
	//ADMUX |= _BV(REFS1) | _BV(REFS0) | _BV(MUX0) | _BV(MUX1) | _BV(MUX2);
	//ADC set upt to chanel 15 + add timer1 compare B trigger
	ADCSRB |= _BV(MUX5) | _BV(ADTS2) | _BV(ADTS0);
	//Enable ADC: Div fact:128, interupt enabled
	ADCSRA |= _BV(ADEN) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
	sei();
}

ISR(ADC_vect) {
	//cache conversion result in sample 
	sample = ADC;
	//convert voltage to temp
	result = sample; // TODO: add calculation here.

	//call the callback function with the result
	cb(result);
}
