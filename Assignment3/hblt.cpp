#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <typeinfo>

//Name:				Nicolas Fry
//UF ID:			
//GatorID:			nicolascoding
//Discussion Section: 1085
//Assignment 3
//Height Biased Leftist Tree implementation 

template<class T>
class hblt 
{
	public:
		hblt();
		~hblt();
		bool empty() const;			
		int size() const;			
		void push(T val);			
		T top() const;			
		void pop();					
		bool full() const;			
		void print() const;

		//specific to assignment
		int getSum() const;		

	private:
		struct node
		{
			//next node
			node* leftChild;
			node* rightChild;
			T data;
			// int sVal = 0;
			node(T dat)
			{
				leftChild = 0;
				rightChild = 0;
				data = dat;
			}

		};
		int amountOfElements;
		int sum;
		node* root;
		typename hblt<T>::node* meld(node* leftB, node* rightB);
		int getSVal(node* n);

		//used for destructor
		void deleteAllSouthof(node* n);
};

template<class T>
int hblt<T>::getSum() const
{
	return sum;
}

template<class T>
bool hblt<T>::empty() const
{
	return root == 0;
}

template<class T>			
int hblt<T>::size() const
{
	return amountOfElements;
}

template<class T>
void hblt<T>::push(T dat)
{
	node *val = new node(dat);
	if(size() == 0)
	{
		// std::cout<<"loc 1" << std::endl;
		root = val;
		amountOfElements+=1;

		//specific to assignment
		sum+= int(dat);
		// std::cout<<"init root: " << root->data << std::endl;
		return;
	}

	// std::cout<<"loc 2" << std::endl;
	root = meld(root, val);
	// std::cout<<"root: " << root->data << std::endl;
	amountOfElements+=1;

	//specific to assignment
	sum+= int(dat);
	// std::cout << "new sum: " << sum << std::endl;
}

template<class T>			
T hblt<T>::top() const
{
	if(size() > 0)
		return root->data;

	std::cout << "Tree is empty!" <<std::endl;
	return 0;
}			

template<class T>
void hblt<T>::pop()
{
	if(size() == 0)
	{
		std::cout << "Tree is empty!" << std::endl;
		return;
	}	

	sum-=top();
	// std::cout << "new sum: " << sum << std::endl;

	node* leftB = root->leftChild;
	node* rightB = root->rightChild;
	node* toDelete = root;

	root = meld(leftB, rightB);
	delete toDelete;
	amountOfElements-=1;
	std::cout << "Amount of elements "<< size() << std::endl;
}		

template<class T>
typename hblt<T>::node* hblt<T>::meld(node* leftB, node* rightB)
{
	if(leftB == 0)
	{
		// std::cout << "returning rightB" << std::endl;
		return rightB;
	}

	if(rightB == 0)
	{
		// std::cout << "returning leftB" << std::endl;
		return leftB;
	}

	// std::cout << "Leftbranch's data: " << leftB->data << " Rightbranch's data: " << rightB->data <<std::endl;
	if(leftB->data > rightB->data)
	{
		// std::cout << "Leftbranch's data > rightbranch's data" << std::endl;
		// std::cout << "Leftbranch's data: " << leftB->data << " Rightbranch's data: " << rightB->data <<std::endl;
		node *holder = leftB;
		leftB = rightB;
		rightB = holder;
		// std::cout << "leftbranch and rightbranch swapped new data's:" << std::endl;
		// std::cout << "Leftbranch's data > rightbranch's data" << std::endl;
		// std::cout << "Leftbranch's data: " << leftB->data << " Rightbranch's data: " << rightB->data <<std::endl;
		
	}
	// std::cout << "Checkpoint1" << std::endl;
	leftB->rightChild = meld(leftB->rightChild, rightB);
	// std::cout << "Checkpoint2" << std::endl;

	if(leftB->leftChild == 0)
	{
		// std::cout << "Checkpoint3" << std::endl;
		leftB->leftChild = leftB->rightChild;
		leftB->rightChild = 0;
	}
	else
	{
		// std::cout << "Checkpoint4" << std::endl;
		// std::cout<< "leftB->leftChild " << leftB->leftChild << " rightB->rightChild " << rightB->rightChild << std::endl;
		if(getSVal(leftB->leftChild) < getSVal(rightB->rightChild))
		{
			// std::cout << "Checkpoint5" << std::endl;
			node* holder = leftB->leftChild;
			leftB->leftChild = leftB->rightChild;
			leftB->rightChild = holder;
		}
	}
	// std::cout << "returning left branch" << std::endl;
	return leftB;
}

template<class T>
int hblt<T>::getSVal(node* n)
{
	//according to slides, the rightmost node yields the shortest path
	int amount = 1;

	if(n == 0)
	{
		return amount;
	}

	node* traverse = n;
	while(traverse->rightChild != 0)
	{
		amount+=1;
		traverse= traverse->rightChild;
	}
	return amount;
}

//constructor
template<class T>
hblt<T>::hblt()
{
	root = 0;
	amountOfElements = 0;
}

//Destructor implementation
template<class T>
hblt<T>::~hblt()
{
	deleteAllSouthof(root);
}

template<class T>
void hblt<T>::deleteAllSouthof(node* n)
{
	if(n == 0)
	{
		return;
	}
	node* toDelete = n;

	node* LeftBranchNode = n->leftChild;
	node* RightbranchNode = n->rightChild;

	delete toDelete;

	deleteAllSouthof(LeftBranchNode);
	deleteAllSouthof(RightbranchNode);
}



