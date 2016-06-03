#include "Ringbuffer.h"
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

#ifndef Ringbuffer_cpp
#define Ringbuffer_cpp

//ctor
template<typename inType, unsigned int maxSize>
Ringbuffer<inType, maxSize>::Ringbuffer() {
	inType Array[maxSize]{};
}


template<typename inType, unsigned int maxSize>
inType Ringbuffer<inType, maxSize>::front() { return Array[first_ptr]; }

template<typename inType, unsigned int maxSize>
unsigned int Ringbuffer<inType, maxSize>::size() { return length; }

template<typename inType, unsigned int maxSize>
void Ringbuffer<inType, maxSize>::enqueue(const inType& inValue) {
	/*
	* save the old pointers, perhaps the will be needed,
	* (when Array have been enqueued more
	* often than it's maximum number of elements it can contain)
	*/
	unsigned int old_max_ptr = max_ptr;
	unsigned int old_min_ptr = min_ptr;

	//special case: adding first element
	if (0 != length)
		last_ptr = (++last_ptr) % maxSize;

	Array[last_ptr] = inValue;

	if (Array[max_ptr] < inValue)
		max_ptr = last_ptr;

	if (Array[min_ptr] > inValue)
		min_ptr = last_ptr;

	if (length < (maxSize))
		++length;
	//changes for the case, that more elements enqueued, than Array can contain:
	else {
		first_ptr = (++first_ptr) % maxSize;
		if (last_ptr == old_min_ptr)
			min_ptr = searchNextMinElem();
		if (last_ptr == old_max_ptr)
			max_ptr = searchNextMaxElem();
	}
};

template<typename inType, unsigned int maxSize>
void Ringbuffer<inType, maxSize>::dequeue() {
	if (length == 0)//no elements in Ring
		std::cerr << "Error: too few elements to dequeue.\n";
	else {
		//if lowest element has been dequeed
		if (first_ptr == min_ptr)
			min_ptr = searchNextMinElem();
		//if hightest element has been dequeed
		if (first_ptr == max_ptr)
			max_ptr = searchNextMaxElem();

		if (length != 1)
			first_ptr = (++first_ptr) % maxSize;

		--length;
	}
};

template<typename inType, unsigned int maxSize>
inType Ringbuffer<inType, maxSize>::getMax() { return Array[max_ptr]; };

template<typename inType, unsigned int maxSize>
inType Ringbuffer<inType, maxSize>::getMin() { return Array[min_ptr]; }

template<typename inType, unsigned int maxSize>
bool Ringbuffer<inType, maxSize>::contains(const inType&  elem) const
{	//special case: false  - when elem out of the interval of the Array's elements
	if ((elem < Array[min_ptr] )|| (elem > Array[max_ptr]))
		return false;
	//normal case - search
	else {
		for (auto i = 0; i != length; ++i)
			if (elem == (*this)[i])
				return true;
			else
				return false;
	}
}

template<typename inType, unsigned int maxSize>
inType const& Ringbuffer<inType, maxSize>::operator[] (const unsigned int& idx) const{
	return (Array[(idx + first_ptr) % maxSize]);
}

template<typename inType, unsigned int maxSize>
unsigned int Ringbuffer<inType, maxSize>::searchNextMaxElem() {
	if (length == 0)
		return 0;
	else {
		//start searching:
		unsigned int currentMax_ptr = min_ptr;
		for (auto i = 0; i != length; ++i) {
			/*
			* search for next element, when:
			* 1.: overwritten		--> normal loop	(search all elements)	--> that's why max_ptr!=last_ptr
			* 2.: deques max_ptr	--> don't search when i == max_ptr(old max)
			*/
			if (((i + first_ptr) % maxSize != max_ptr) || (max_ptr == last_ptr))
				if ((*this)[i] > Array[currentMax_ptr])
					currentMax_ptr = (i + first_ptr) % maxSize;
		}
		return currentMax_ptr;
	}
}

template<typename inType, unsigned int maxSize>
unsigned int Ringbuffer<inType, maxSize>::searchNextMinElem() {
	if (length == 0)
		return 0;
	else {
		//start search:
		unsigned int currentMin_ptr = max_ptr;
		for (auto i = 0; i != length; ++i) {
			/*
			* search for next element, when:
			* 1.: overwritten		--> normal loop	(search all elements)	--> that's why i!=last_ptr
			* 2.: deques min_ptr	--> don't search when i == min_ptr(old min)
			*/
			if (((i+first_ptr)%maxSize != min_ptr) || (min_ptr == last_ptr))
				if ((*this)[i] < Array[currentMin_ptr])
					currentMin_ptr = (i+first_ptr)%maxSize;
		}
		return currentMin_ptr;
	}
}

#endif//Ringbuffer_cpp
