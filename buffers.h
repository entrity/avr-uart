#ifndef BUFFERS_H
#define BUFFERS_H

#define BYTE_BUFFER_LEN 20
#define BIT_BUFFER_LEN 8

// Byte buffer
typedef struct {
	char buffer[BYTE_BUFFER_LEN];
	volatile char s; // offset to the start of unread items in this buffer
	volatile char e; // offset to the last of unread items in this buffer
	volatile char n;
	volatile bool lock;
} byte_buffer_t;

// Bit buffer
typedef struct {
	char buffer;
	volatile char n;
	volatile bool lock;
} bit_buffer_t;

// Adds a bit to a buffer. Returns true if buffer is full
char pushBitToBuffer(bit_buffer_t *, bool);

// set initial values
void initByteBuffer(byte_buffer_t *);

// Adds a byte to a buffer. Returns length of contents in buffer.
int pushByteToBuffer(byte_buffer_t *, char);

#endif