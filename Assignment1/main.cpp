#include <iostream>
#include "CircleLL.cpp"

int main()
{
	CircleLL<int> * circList = new CircleLL<int>();

	circList->PrintLL();
	//std:: cout << "size: " << circList->size() << std::endl;
	circList->Insert(0, 3);
	circList->PrintLL();
	//std:: cout << "size: " << circList->size() << std::endl;
	circList->Insert(0, 5);
	circList->PrintLL();
	//std:: cout << "size: " << circList->size() << std::endl;
	circList->Insert(4, 7);
	circList->PrintLL();
	//std:: cout << "size: " << circList->size() << std::endl;
	circList->Insert(6, 9);
	circList->PrintLL();
	//std:: cout << "size: " << circList->size() << std::endl;
	circList->Insert(2,22);	
	circList->PrintLL();
	circList->Insert(5,23);
	circList->PrintLL();
	circList->Insert(6,24);
	circList->PrintLL();
	//std:: cout << "size: " << circList->size() << "\n" << std::endl;
	//broken here
	circList->Insert(6,25);
	circList->PrintLL();
	//std:: cout << "size: " << circList->size() << "\n" << std::endl;

	circList->Insert(6,88);
	circList->PrintLL();

	std:: cout << "removeTest" << std:: endl;
	circList->PrintLL();


	circList->RemoveAtIndex(0);
	circList->PrintLL();

	circList->RemoveAtIndex(2);
	circList->PrintLL();

	circList->RemoveAtIndex(circList->size());
	circList->PrintLL();

	
	//circList->PrintAtElement(10);

}
