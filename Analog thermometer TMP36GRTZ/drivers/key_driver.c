/*
 * key_driver.c
 *
 * Created: 2022-02-18 1:29:07 PM
 *  Author: pente
 */ 
#include "key_driver.h"
uint8_t key_state;

void init_keys()
{
	//set up input for swithes;
	DDRC &= ~( 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 );
	PORTC |= 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 ;
	DDRD &= ~(1 << 2 | 1 << 3);
	PORTD |= 1 << 2 | 1 << 3;
	MCUCR &= ~(1<<PUD); //clear PUD bit in SFIOR for internal pull-up.
}


uint8_t get_key(uint8_t key_no) //key 1-8
{
	key_no--;
	if(key_no<6){
		key_state = PINC & _BV(key_no);
	}else{
		key_no -= 4;
		key_state = PIND & _BV(key_no);
	}
	if ((key_state)==0)
	{
		return 1;
	}
	return 0;
	
}

uint8_t scan_key()
{
	for (uint8_t i = 1; i <= 8; i++ ) {
		if (get_key(i) == 1) {
			return i;
		}
	}
	return 0;
}
