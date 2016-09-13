/*
 * ring_buffer.h
 *
 *  Created on: Sep 13, 2016
 *      Author: Kaustubh
 */

#ifndef RINGBUFFER_RING_BUFFER_H_
#define RINGBUFFER_RING_BUFFER_H_

#include "../commondef.h"
#include <string.h>

#define RBUFF_SIZE 64

class RingBuffer {
public:
	RingBuffer();
	~RingBuffer();
	void init();
	bool isEmpty();
	bool isFull();
	bool put(uint8_t b);
	int32_t get();
	void flush(bool clear);

private:
	uint8_t increment(uint8_t b);
	uint8_t buff[RBUFF_SIZE];
	uint8_t head;
	uint8_t tail;
	uint8_t count;

};

#endif /* RINGBUFFER_RING_BUFFER_H_ */
