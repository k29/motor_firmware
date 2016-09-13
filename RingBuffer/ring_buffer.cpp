/*
 * ring_buffer.cpp
 *
 *  Created on: Sep 13, 2016
 *      Author: Kaustubh
 */

#include "ring_buffer.h"

RingBuffer::RingBuffer() {

}

RingBuffer::~RingBuffer() {

}


/***
 * This function clears
 * -> buff
 * -> head
 * -> tail
 * -> count
 * -> sets head = tail
 ***/
void RingBuffer::init(){

	memset(buff, 0, sizeof(buff));
	head = tail = count = 0;
}

bool RingBuffer::isEmpty(){
	if(count == 0)
		return true;
	else
		return false;
}

bool RingBuffer::isFull(){
	if(count == RBUFF_SIZE)
		return true;
	else
		return false;
}

/***
 * This function returns int32_t
 * -1 -> signifies could not get.
 * Returns the current tail position element
 * increments the position of the tail pointer
 ***/

int32_t RingBuffer::get(){

	int32_t c;
	if(count != 0){
		c = buff[tail];
		tail = increment(tail);
		--count;
	}
	else
		c = -1;
	return c;

}


/***
 * This function returns bool, true =  if operation success,
 * else false if overflow
 * Inserts an element in the next head position
 ***/
bool RingBuffer::put(uint8_t b){
	if(count < RBUFF_SIZE){
		buff[head] = b;
		head = increment(head);
		++count;
	}
	return false;
}


/***
 * We set the parameters value to be 0
 * if clear == true, then buffer is set to 0
 ***/
void RingBuffer::flush(bool clear){
	count = 0;
	head = 0;
	tail = 0;
	if (clear){
		memset(buff, 0, sizeof(buff));
	}
}

uint8_t RingBuffer::increment(uint8_t b){
	return ((b+1) % (RBUFF_SIZE));
}

