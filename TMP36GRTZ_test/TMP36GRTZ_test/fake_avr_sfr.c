//                      fake_avr_sfr.c
// Fake AVR Special Function Registers used for Unit Tests
// Author: Erland Larsen, VIA University College
// Date: 12-01-2021
// #pragma once

#include <avr/io.h>

	uint8_t __avr_reg[_HIGHEST_REGISTER_ADDR];
	uint8_t __SREG;
