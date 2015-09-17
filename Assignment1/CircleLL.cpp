#include <iostream>
#include <sstream>
#include <algorithm>

//	Nicolas Fry	
//	COP3503
//	Programming Assignment 1
//	Circular Linked List
//	Intended to be used with the Josephus problem

template<class T>
class CircleLL
{
	public:
		CircleLL();
		void Insert(int index, const T &data);
		void PrintLL() const;
		int size() const;
		void PrintAtElement(int index) const;
		T getElementValue(int index) const;
		typename CircleLL<T>::node* getElement(int index) const;
		void RemoveAtIndex(int index);
		bool isRoot(int index) const;
		~CircleLL();

		//psuedoIteratorFunctions
		void toBeginIter();
		void toEndIter();
		bool moveForward(); //returns true if passed the beginning of the circle
		int getIterPos();
		void removeAtIter(int offset);

	private:
		struct node
		{
			//next node
			node* next;
			bool isRoot;
			T data;
		};

		node *root;
		node *last;

		//to Solve Josephus problem, I am creating a sudo Iterator to go ahead and move positions.
		node *psuedoIterator;
		int psuedoIteratorIndex;
};


//constructor
template<class T>
CircleLL<T>::CircleLL()
{
	root = 0;		//initialize root and last pointers to null
	last = 0;
	psuedoIterator = 0;
	psuedoIteratorIndex = -1;
}

//Destructor implementation
template<class T>
CircleLL<T>::~CircleLL()
{
	int fullsize = size();	//Figure out size and deallocate each memory address
	node * toDelete; 
	int i = 0;
	while(i++ < fullsize)
	{
		toDelete = root;
		root = root->next;
		delete toDelete;
	}
}

//insert T data to index index
template<class T>
void CircleLL<T>::Insert(int index, const T &data)
{

	//Case 1: List is empty
	if(root == 0)
	{
		root = new node;
		root->isRoot = true;
		root->data = data;

		//point the next portion back to itself
		root->next = root;
		last = root;
		return;
	}


	//List is not empty so create node;
	node * toBeAdded = new node;
	toBeAdded->data = data;

	//Case 2: Want to insert at position 0 aka root
	//    	endNode ----> root
	//		endNode ----> tobeadded(new root) ------>  (old root)
	//made index % size() + 1 because we may want to tack on a element to the end,
	//anything after end will loop around
	if(index == 0 || index % (size()+1) == 0)
	{

		//Point new root to original root 
		toBeAdded->isRoot = true;
		toBeAdded->next = root;

		//Switch root to no longer be root
		root->isRoot = false;

		//new root is toBeAdded, and tell last node to point to new root
		root = toBeAdded;
		last->next = root;

		return;
	}

	//we know at this point that the node will not be root,
	toBeAdded->isRoot = false;

	//Case 3: Want to insert at nth position
	//Traverse to position
	node * current = root;
	int n = 0;
	while(n++ < index-1)
	{
		current = current->next;
	}

	//if inserting at the end, declare it to be the last element
	if(index % size() == 0)
	{
		last = toBeAdded;
	}	

	//Insert it in
	toBeAdded->next = current->next;
	current->next = toBeAdded;	

	

}

template<class T>
void CircleLL<T>::PrintLL() const
{
	
	if(size() == 0)
	{
		std::cout << "No items in list" << std::endl;
		return;
	}

	node *current = root;

	//Create string stream
	std::stringstream ss;
	ss<< '[';
	do
	{
		ss <<  current->data <<",";

		current = current->next;
	}
	while(current->isRoot != true);

	std::string toPrint = ss.str().substr(0, ss.str().size()-1);
	std::cout << toPrint << "]" << std:: endl;
}

//PsuedoIterator functions
template<class T>
void CircleLL<T>::toBeginIter()
{
	psuedoIteratorIndex = 0;
	psuedoIterator = root;
}

template<class T>
void CircleLL<T>::toEndIter()
{
	psuedoIteratorIndex = size()-1;
	psuedoIterator = last;
}

template<class T>
bool CircleLL<T>::moveForward()
{
	psuedoIterator=psuedoIterator->next;

	if(psuedoIterator == root)
	{
		psuedoIteratorIndex = 0;
		return true;
	}
	else
	{
		psuedoIteratorIndex++;
	}
	return false;
}

template<class T>
int CircleLL<T>::getIterPos()
{
	return psuedoIteratorIndex;
}

//moves iterator offset forward, then deletes the position it was at
template<class T>
//0, 1, 2, 3, 4
//		^
//0, 1, 2, 3, 4
//		%	  ^
//
//0, 1, 3, 4
//		   ^	
void CircleLL<T>::removeAtIter(int offset)
{
	node * toDelete = psuedoIterator;
	int indexOfDelete = getIterPos();
	bool passedBeginningOfCircle = false;
	for(int i = 0; i < offset; i++)
	{
		if(moveForward())
		{
			passedBeginningOfCircle = true;
		}
	}

	
	RemoveAtIndex(indexOfDelete);

	//account for removal of element by subtracting one
	if(!passedBeginningOfCircle)
	{
		psuedoIteratorIndex--;
	}

}



template<class T>
int CircleLL<T>::size() const
{
	if(root == 0)
		return 0;

	node * current = root;

	int count = 0;
	do
	{
		count++;
		current=current->next;
	}
	while(current->isRoot != true);
	return count;
}

template<class T>
void CircleLL<T>::PrintAtElement(int index) const
{
	std::cout << getElementValue(index) << std::endl;
}

template<class T>
T CircleLL<T>::getElementValue(int index) const
{
	return getElement(index)->data;
}

template<class T>
typename CircleLL<T>::node* CircleLL<T>::getElement(int index) const
{
	if(size() == 0)
	{
		std::cout << "No items in list" << std::endl;
		return NULL;
	}

	node *current = root;

	int i = 0;
	while(i++ < index)
	{
		current = current->next;
	}

	return current;
}

template<class T>
void CircleLL<T>::RemoveAtIndex(int index)
{
	//Case 1: List is empty
	if(root == 0)
	{
		std::cout << "Nothing to remove! List is empty" << std::endl;
		return;
	}

	//if removing last element in the list, delete root and null out first and last pointers
	if(size() == 1)
	{
		delete root;
		root = 0;
		last = 0;
		return;
	}

	node * toDelete;

	//Case 2: Want to remove at position 0 aka root
	//    	endNode ----> root ----> indexOfRoot+1
	//		endNode ----> indexOfRoot+1 (new root)
	if(index == 0 || index % size() == 0)
	{
		//std::cout << "Deleting root!" << std:: endl;
		//std::cout << "Last's data " << last->data << std::endl;
		//std::cout << "Last->next's data " << last->next->data << std::endl;
		//std::cout << "Root's data " << root->data << std::endl;
		last->next = root->next;
		root->next->isRoot = true;

		//store root in temp pointer which will be deleted
		toDelete = root;
		root = root->next;
		delete toDelete;

		return;
	}

	//Case 3: Want to delete at nth position
	//Traverse to position
	node * current = root;
	int n = 0;

	while(n++ < index-1)
	{
		//std::cout << "Data: " << current->data << std:: endl;
		current = current->next;
	}

	//if deleting at the end, reassign the last element
	if((index + 1)  % size() == 0)
	{
		//std:: cout << "index: " << index << std:: endl;
		//std:: cout << "size: " << size() << std:: endl;
		//std:: cout << "index % size()-1: " << (index % size()-1) << std::endl;
		//std::cout << "Reassigning last node to node with data "<< current->data << std::endl;
		last = current;
	}	

	//Remove it
	toDelete = current->next;
	//std::cout << "Deleting node: " << toDelete->data << std::endl;
	current->next = current->next->next;
	delete toDelete;
}

template<class T>
bool CircleLL<T>::isRoot(int index) const
{
	return getElement(index)->isRoot;
}

/*
19
I 1 0
I 2 1
I 3 2
I 4 3
I 5 4
I 6 5
I 7 6 
I 8 7 
I 9 8
I 10 9
I 0 2
D 5
J 3 2 34 23 22
*/