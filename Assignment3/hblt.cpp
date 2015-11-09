#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <typeinfo>

//Name:				Nicolas Fry
//UF ID:			
//GatorID:			nicolascoding
//Discussion Section: 1085
//Assignment 3s
//Height Biased Leftist Tree implementation 

template<class T>
class hblt 
{
	public:
		hblt();
		~hblt();
		bool empty() const;			
		int size() const;			
		void push(T* val);			
		T* top() const;			
		void pop();								
		void print() const;

		//specific to assignment
		// int getSum() const;		

	private:
		struct node
		{
			//next node
			node* leftChild;
			node* rightChild;
			T* data;
			int sVal;
			// int sValz = 0;
			node(T* dat)
			{
				leftChild = 0;
				rightChild = 0;
				data = dat;
				sVal = 1;
			}

		};
		int amountOfElements;
		// int sum;
		node* root;
		typename hblt<T>::node* meld(node* leftB, node* rightB);

		//made this to try and understand s-value better
		int getSVal(node* n);

		//used for destructor
		void deleteAllSouthof(node* n);
};

// template<class T>
// int hblt<T>::getSum() const
// {
// 	return sum;
// }

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
void hblt<T>::push(T* dat)
{
	node *val = new node(dat);
	if(size() == 0)
	{
		root = val;
		amountOfElements+=1;
		return;
	}

	root = meld(root, val);
	amountOfElements+=1;
}

template<class T>			
T* hblt<T>::top() const
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

	node* leftB = root->leftChild;
	node* rightB = root->rightChild;
	node* toDelete = root;

	root = meld(leftB, rightB);
	delete toDelete;
	amountOfElements-=1;
}		

template<class T>
typename hblt<T>::node* hblt<T>::meld(node* leftB, node* rightB)
{
	if(leftB == 0)
	{
		return rightB;
	}

	if(rightB == 0)
	{
		return leftB;
	}

	if(*leftB->data > *rightB->data)
	{
		node *holder = leftB;
		leftB = rightB;
		rightB = holder;		
	}

	leftB->rightChild = meld(leftB->rightChild, rightB);

	if(leftB->leftChild == 0)
	{
		leftB->leftChild = leftB->rightChild;
		leftB->rightChild = 0;
	}
	else
	{
		int leftBsVal = 0;
		int rightBsVal = 0;

		if(leftB->leftChild != 0)
		{
			leftBsVal = leftB->leftChild->sVal;
		}

		if(rightB->rightChild != 0)
		{
			rightBsVal = rightB->rightChild->sVal;
		}


		if(leftBsVal < rightBsVal)
		{
			node* holder = leftB->leftChild;
			leftB->leftChild = leftB->rightChild;
			leftB->rightChild = holder;
		}

		if(leftB->rightChild != 0)
		{
			leftB->sVal = leftB->rightChild->sVal + 1;
		}

		else
		{
			leftB->sVal = 1;
		}
	}
	return leftB;
}

//not used in latest version, but a decent function to have
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



