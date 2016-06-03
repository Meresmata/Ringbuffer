/*
implementation of a ring buffer with a hard-coded maximum length
64 elements for 8 bit avr micros, else 128 elements
older elements will overwritten if the maximum number of elements is reached
(by using an old c-style array)

using following standard methods:
	front
	enqueue
	dequeue

in addition:
	size
	[] - to GET all Elements in the list
	getMax - get the element with highetst value (musst be compareble)
	getMin - get the element with lowest value
	contains

*/


#ifndef Ringbuffer_h
#define Ringbuffer_h


#ifndef __AVR__
#include <iostream>
#include <iomanip>

#endif// __AVR__

#include <stdbool.h>

//circular buffer of given type and length
template<typename inType = int, unsigned int maxSize= 64>
class Ringbuffer {
public:

	//create a ring buffer with the given number of elements
	Ringbuffer();

	//Returns the first element of the ring
	inline inType front();

	//returns current length()
	unsigned int size();

	//enqueues an element into the ring(adds the element in the last position)
	//one element: the element that shall be add
	void enqueue(const inType &inValue);

	//dequeues the first element of the ring
	void dequeue();

	//return the element with highest value
	inType getMax();
	//return element with the lowest value
	inType getMin();

	//tests whether element is included
	bool contains(const inType& elem) const;

	inType const& operator[] (const unsigned int& idx)const;

private:
	inType Array[maxSize];
	unsigned int first_ptr	= 0;
	unsigned int last_ptr	= 0;
	unsigned int length = 0;//the actual length of the buffer


	//those will complicate the code, will implement their usage later
	unsigned int max_ptr	= 0;//shows to the element with the maximal value
	unsigned int min_ptr	= 0;////shows to the element with the maximal value

	unsigned int searchNextMaxElem();
	unsigned int searchNextMinElem();
};
#include "Ringbuffer.cpp"

#endif//Ringbuffer
