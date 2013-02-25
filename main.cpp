/* This setup is for ATmega328 */

#include <avr/io.h>
#include <util/delay.h>
#include "bar.h"

void 

int main()
{
  // enable serial for outputting to monitor
  Serial.begin(2400);
  // configure INT0 interrupt for falling edge
  MCUCR |= (2 << ISC00);
  // enable interrupt on INT0 (PD0)
  EIMSK |= (1 << INT0);
  // enable global interrupts
  sei();
}


// ISR when the start bit arrives at pin INT0
ISR(INT0_vect)
{
	/* store SREG value */
  char cSREG;
  cSREG = SREG;
  // enable timer-based ISR to catch remaining bits in this character

  // do I need to disable this ISR while the other one runs?

  /* restore SREG value (I-bit) */
  SREG = cSREG;
}

// ISR when the timer instructs program to get (non-first) bits from pin INT0
ISR()
{
	// grab bit, load it into bit buffer
	// if byte in BIT_BUFFER is complete, disable this ISR and add byte to BYTE_BUFFER
	// disable this ISR
	// add byte to BYTE_BUFFER
}