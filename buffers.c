#include "buffers.h"

// Adds a bit to a buffer. Returns number of bits loaded.
char pushBitToBuffer(bit_buffer_t * p_bitBuffer, bool input)
{
	if (p_bitBuffer->n >= BIT_BUFFER_LEN)
		return BIT_BUFFER_LEN;
	// load bit to buffer
	if (input)
		p_bitBuffer->buffer |= (1 << p_bitBuffer->n); 
	else
		p_bitBuffer->buffer &= ~(1 << p_bitBuffer->n);
	// increment buffer count
	p_bitBuffer->n ++;
	// return bit count
	return p_bitBuffer->n;
}

// Sets initial values
void initByteBuffer(byte_buffer_t * p_byteBuffer)
{
	p_byteBuffer->s = 0;
	p_byteBuffer->e = 0;
	p_byteBuffer->n = 0;
	p_byteBuffer->lock = 0;
}

// Adds a byte to a buffer. Returns length of contents in buffer. Returns -1 if buffer is full (and therefore rejects the input).
int pushByteToBuffer(byte_buffer_t * p_byteBuffer, char input)
{
	// fail if buffer is full
	if (p_byteBuffer->n >= BYTE_BUFFER_LEN)
		return -1;
	// increment end of buffer
	p_byteBuffer->e = (p_byteBuffer->e + sizeof(char)) % BYTE_BUFFER_LEN;
	// push byte to buffer
	p_byteBuffer->buffer[p_byteBuffer->e] = input;
	// increment buffer count
	p_byteBuffer->n ++;
	// return count of unread items in buffer
	return p_byteBuffer->n;
}