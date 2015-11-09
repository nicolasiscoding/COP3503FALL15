#include <iostream>
#include "Machine.cpp"

int main()
{
	Machine i = Machine();
	i.addJob(5);
	i.addJob(2);
	i.addJob(1);

	Machine j = Machine();
	j.addJob(3);
	j.addJob(1);
	std:: cout << i << std::endl;
	std:: cout << j << std::endl;

	std:: cout << (i > j) << std::endl;
	std:: cout << (i < j) << std::endl;
	std:: cout << (i >= j) << std::endl;
	std:: cout << (i <= j) << std::endl;
	std:: cout << (i == j) << std::endl;

}