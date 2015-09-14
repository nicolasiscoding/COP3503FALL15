#include <iostream>
#include <sstream>

//	Nicolas Fry	
//	COP3503
//	Programming Assignment 1
//	Circular Linked List
//

template<class T>
class CircleLL
{
	public:
		CircleLL();
		void Insert(int index, const T &data);
		void PrintLL() const;
		int size() const;
		void PrintAtElement(int index) const;
		void RemoveAtIndex(int index);
		~CircleLL();

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
};


//constructor
template<class T>
CircleLL<T>::CircleLL()
{
	root = 0;
	last = 0;
}

//Destructor implementation
template<class T>
CircleLL<T>::~CircleLL()
{
	int fullsize = size();
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
		std::cout << "In empty case" << std::endl;
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
	if(index == 0 || index % size() == 0)
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

	//Case 3: Want to insert at nth position
	//Traverse to position
	node * current = root;
	int n = 0;
	while(n++ < index-1)
	{
		current = current->next;
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
	do
	{
		ss <<  current->data <<" ";

		current = current->next;
	}
	while(current->isRoot != true);

	ss << "\n";

	std::cout << ss.str() << std:: endl;
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
	if(size() == 0)
	{
		std::cout << "No items in list" << std::endl;
		return;
	}

	node *current = root;

	int i = 0;
	while(i++ < index)
	{
		current = current->next;
	}

	std::cout << current->data << std:: endl;
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

	node * toDelete;

	//Case 2: Want to remove at position 0 aka root
	//    	endNode ----> root ----> indexOfRoot+1
	//		endNode ----> indexOfRoot+1 (new root)
	if(index == 0 || index % size() == 0)
	{
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
		current = current->next;
	}

	//Insert it in
	toDelete = current->next;
	current->next = current->next->next;
	delete toDelete;
}