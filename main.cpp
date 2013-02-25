/* This setup is for ATmega328 */

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "buffers.h"
#define READ_BIT(x,y) (((x)>>(y)) & 1) 

byte_buffer_t byteBuffer;
bit_buffer_t bitBuffer;

void enableTimerBasedIsr()
{

}

void disableTimerBasedIsr()
{

}

void initTimer()
{

}

int main()
{
  // enable serial for outputting to monitor
  // Serial.begin(2400);
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
  enableTimerBasedIsr();
  // do I need to disable this ISR while the other one runs?

  /* restore SREG value (I-bit) */
  SREG = cSREG;
}

// ISR when the timer instructs program to get (non-first) bits from pin INT0
ISR(TIM0_COMPA_vect)
{
	// grab bit from pin
	bool bit = READ_BIT(PORTD, PD0);
	// load bit into bit buffer
	char bitsInBuffer = pushBitToBuffer(&bitBuffer, bit);
	// if byte in bitBuffer is complete, disable this ISR and add byte to byteBuffer
	if ( bitsInBuffer == BIT_BUFFER_LEN ) {
		// must I enable falling-edge interrupt?

		// disable this ISR
		disableTimerBasedIsr();
		// add byte to byteBuffer
		pushByteToBuffer(&byteBuffer, bitBuffer.buffer);
	}
}