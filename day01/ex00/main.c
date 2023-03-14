#include <avr/io.h>

int main()
 { 
   DDRB |= (1<<PB0);	//make PORT B pin 0 an output pin
	
	TCNT0 = 206;	//load TCNT0 with 206 for  50us delay
	//configure timer0 for normal mode with pre-scalar of 8
	TCCR0A =0x00;
	TCCR0B |= (1<<CS01);		
	// TIMSK0 |= (1<<TOIE0);		// enable timer overflow interrupt
	// sei();			//enable global interrupt
	
   while (1);

   return 0;
 }

// ISR(TIMER0_OVF_vect){
// 	TCNT0 = 206;
// 	PORTB ^= (1<<PB0);

// }