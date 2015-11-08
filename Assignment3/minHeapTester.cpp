#include "minHeap.cpp"
#include <iostream> 
int main()	
{
	minHeap* a = new minHeap();
	a->push(5);
	a->print();

	std::cout<< "\n" << std::endl;

	a->push(2);
	a->print();

	std::cout<< "\n" << std::endl;


	a->push(6);
	a->print();

	std::cout<< "\n" << std::endl;

	a->push(1);
	a->print();

	std::cout<< "\n" << std::endl;

	a->push(9);
	a->print();

	std::cout<< "\n" << std::endl;

	a->push(65);
	a->print();
	std::cout<< "\n" << std::endl;

	a->push(7);
	a->print();

	std::cout<< "\n" << std::endl;

	a->push(3);
	a->print();

	//top and pop test

	std::cout << a->top() << std::endl;
	a->pop();
	a->print();

	a->pop();
	a->print();

	// a->pop();
	// a->print();
}