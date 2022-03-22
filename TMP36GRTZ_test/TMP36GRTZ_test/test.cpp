#include "gtest/gtest.h"

extern "C" {
#include <avr/io.h>
#include "TMP36GRTZ.h"
}

class TMP36GRTZ_test : public ::testing::Test {
protected:
	void SetUp()
	{}
	void TearDown()
	{}
};

void dummycalback(float result) {

}

TEST_F(TMP36GRTZ_test, Test_timer_setup) {
	init_termometer(dummycalback);
	EXPECT_EQ(TCCR1A,0);
	EXPECT_EQ(TCCR1B, 0b00001101);
	EXPECT_EQ(TCNT1, 0);
	EXPECT_EQ(OCR1B, 15625);
	EXPECT_EQ(TIMSK1, 0b00000100);
}
TEST_F(TMP36GRTZ_test, Test_adc_setup) {
	EXPECT_EQ(ADMUX, 0b01000111);
	EXPECT_EQ(ADCSRB, 0b00001101);
	EXPECT_EQ(ADCSRA, 0b10101111);
}

TEST_F(TMP36GRTZ_test, Test_calculation_setup) {
	float res= calculate_temp(750);
	EXPECT_EQ(25,res);
}
