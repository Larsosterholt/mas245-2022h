/*
 * Prosjekt1.cpp
 *
 * Created: 19.10.2022 08:16:28
 * Author : dasch
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


double duty;

int main(void)
{
	DDRD = (1 << PD6); //Initialiserer pin 12 som output
	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK0 = (1 << TOIE0);
	
	double dutyNon[101];
	for(int i = 0; i < 101; i++)
	{
		dutyNon[i] = (i*i)/100;
	}
		
	
	
	sei();
	TCCR0B = (1 << CS00) | (1 << CS01);
	
	
	
    while (1) 
    {
		
		for(int i = 0; i < 100; i++)
		{
			_delay_ms(20);
			duty = dutyNon[i];
		}
		for(int i = 0; i < 100; i++)
		{
		
			_delay_ms(20);
			duty = dutyNon[100 - i];
		}
	}
	return 0;
}

ISR(TIMER0_OVF_vect)
{
	OCR0A = (duty/100)*255;
}