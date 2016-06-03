#include "Ringbuffer.h"
#include ".\..\Pair\Pair.h"

#include <iostream>
#include <iomanip>

int main() {
	using coord = Pair<double, double>;

	Ringbuffer<int,3> ring1;
	Ringbuffer<coord,3> ring4;

	std::cout << "Ring ring1 ist: " << ring1.size() << std::endl;
	ring1.enqueue(-4);
	ring1.enqueue(-5);
	ring1.enqueue(-6);
	ring1.enqueue(-7);
	std::cout << "Ring ring1 ist: " << ring1.size() << "Ring beinhaltet -4?"<<ring1.contains(-4)<< "Ring beinhaltet -5?"<< ring1.contains(-5) << std::endl;


	ring1.dequeue();
	ring1.dequeue();
	ring1.dequeue();
	ring1.dequeue();

	ring1.enqueue(-11);
	ring1.enqueue(-12);

	ring4.enqueue(coord{1,1});
	ring4.enqueue(coord{2,2});
	ring4.enqueue({ 2,2 });
}
