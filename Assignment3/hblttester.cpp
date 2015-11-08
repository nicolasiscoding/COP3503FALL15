#include "hblt.cpp"
#include <iostream> 
int main()	
{
	hblt<int>* a = new hblt<int>();
	a->push(5);
	std::cout<< "Top: " << a->top() << std::endl;

	a->push(2);
	std::cout<< "Top: " << a->top() << std::endl;

	a->push(6);
	std::cout<< "Top: " << a->top() << std::endl;

	a->push(1);
	std::cout<< "Top: " << a->top() << std::endl;

	a->push(9);
	std::cout<< "Top: " << a->top() << std::endl;

	a->push(65);
	std::cout<< "Top: " << a->top() << std::endl;

	a->push(7);
	std::cout<< "Top: " << a->top() << std::endl;

	a->push(3);
	std::cout<< "Top: " << a->top() << std::endl;

	std::cout << "Empty: " << a->empty() << std::endl;

	std::cout << "Sum: " << a->getSum() << std::endl;
	std::cout << "Amount of elements " << a->size() << std::endl;

	a->pop();
	std::cout<< "Top: " << a->top() << std::endl;

	a->pop();
	std::cout<< "Top: " << a->top() << std::endl;

	a->pop();
	std::cout<< "Top: " << a->top() << std::endl;

	a->pop();
	std::cout<< "Top: " << a->top() << std::endl;

	a->pop();
	std::cout<< "Top: " << a->top() << std::endl;

	a->pop();
	std::cout<< "Top: " << a->top() << std::endl;

	a->pop();
	std::cout<< "Top: " << a->top() << std::endl;

	a->pop();
	std::cout<< "Top: " << a->top() << std::endl;

	a->pop();
	std::cout<< "Top: " << a->top() << std::endl;

	std::cout << "Empty: " << a->empty() << std::endl;

	std::cout << "Sum: " << a->getSum() << std::endl;

	delete a;
}