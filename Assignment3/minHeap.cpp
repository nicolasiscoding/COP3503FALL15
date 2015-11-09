#include <math.h>
#include <iostream>

//Name:				Nicolas Fry
//UF ID:			
//GatorID:			nicolascoding
//Discussion Section: 1085
//Assignment 3s
//Minimum Heap implementation

template<class T>
class minHeap
{
	public:
		minHeap();					
		~minHeap();					
		bool empty() const;			
		int size() const;			
		void push(T* val);			
		T* top() const;			
		void pop();					
		int capacity() const;		
		bool full() const;			
		void print() const;

	private:
		//methods
		int getLeftChildIndex(int index) const;
		int getRightChildIndex(int index) const;
		int getParentIndex(int index) const;
		void resize();
		void reheapthearray(int index);
		void swap(int pos1, int pos2);

		//vars
		T **minHeapArray;
		int amountOfElements;
		int capacityMultiple; 

};

template<class T>
minHeap<T>::minHeap()
{
	//since 0 is empty, always using (2^n + 1)
	capacityMultiple = 3;

	//initialize minHeapArray to have 3 levels (7 nodes)
	int capacity = pow(2, capacityMultiple);
	minHeapArray = new T*[capacity];

	for (int i = 0; i < capacity; i++)
	{
		minHeapArray[i] = 0;
	}

	amountOfElements = 0;
}

template<class T>
minHeap<T>::~minHeap()
{
	for(int i = 0; i <= capacity(); i++)
	{
		delete minHeapArray[i];
	}

	delete minHeapArray;
}

template<class T>
int minHeap<T>::getLeftChildIndex(int index) const
{
	int cap = capacity();
	if(2 * index > cap)
	{
		return 0;
	}
	return 2 * index;
}

template<class T>
int minHeap<T>::getRightChildIndex(int index) const
{
	int cap = capacity();
	if(2 * index + 1> cap)
	{
		return 0;
	}

	return 2 * index + 1;
}

template<class T>
int minHeap<T>::getParentIndex(int index) const
{
	return index/2;
}

template<class T>
void minHeap<T>::resize() 
{
	//figuring out new capacity and instanciating new array
	int newCapacityMultiple = capacityMultiple + 1;
	int newCapacity = pow(2, newCapacityMultiple);
	T **newArray = new T*[newCapacity];

	//figure out old capacity and copy elements to new minHeap Array
	int oldCapacity = capacity();

	//transfer old items into new array
	for(int i = 0; i <=oldCapacity; i++)
	{
		newArray[i] = minHeapArray[i];
	}

	//initialize rest to zero
	for(int i =oldCapacity+1; i < newCapacity; i++)
	{
		newArray[i] = 0;
	}

	//make new array the minHeap Array
	T **temp = minHeapArray;
	minHeapArray = newArray;
	delete temp;

	//increase the capacity multiple
	capacityMultiple+=1;
}

template<class T>
int minHeap<T>::size() const
{
	return amountOfElements;
}

template<class T>
void minHeap<T>::pop()
{
	if(empty())
	{
		std::cout<< "minHeapArray is empty!" << std::endl;
		return;
	}

	minHeapArray[1] = minHeapArray[amountOfElements];
	minHeapArray[amountOfElements] = 0;
	amountOfElements-=1;

	reheapthearray(1);
}

template<class T>
void minHeap<T>::reheapthearray(int index)
{
	T *currentNode = minHeapArray[index];

	int leftChildIndex = getLeftChildIndex(index);
	T *leftChild = minHeapArray[leftChildIndex];


	int rightChildIndex = getRightChildIndex(index);
	T *rightChild = minHeapArray[rightChildIndex];

	int smallestValueIndex = -1;


	//debug
		// std::cout<< "index: " << index << std::endl;
		// std::cout<< "leftChildIndex: " << leftChildIndex << std::endl;
		// std::cout<< "rightChildIndex: " << rightChildIndex << std::endl;
		// std::cout<< "capacity(): " << capacity() << std::endl;
		// std::cout << "leftChild " << leftChild << std::endl;
		// std::cout << "rightChild " << rightChild << std::endl;
		// if(leftChild != 0)
		// {
		// 	std::cout<< "*leftChild: " << *leftChild << std::endl;
		// 
		// if(rightChild != 0)
		// {
		// 	std::cout<< "*rightChild: " << *rightChild << std::endl;
		// }
		// if(currentNode!= 0)
		// {
		// 	std::cout<< "*currentNode " << *currentNode << std::endl;
		// }
		// std::cout << "size() " << size() << std::endl;



	if(leftChildIndex <= capacity() && leftChild!=0 && *leftChild < *currentNode)
	{
		smallestValueIndex = leftChildIndex;
		currentNode = leftChild;
	}
	
	if(rightChildIndex <= capacity() && rightChild!= 0 && *rightChild < *currentNode)
	{
		smallestValueIndex = rightChildIndex;
	}

	if(smallestValueIndex == -1)
	{
		return;
	}

	swap(index, smallestValueIndex);
	reheapthearray(smallestValueIndex);

}

template<class T>
void minHeap<T>::swap(int pos1, int pos2)
{
	T* temp = minHeapArray[pos1];
	minHeapArray[pos1] = minHeapArray[pos2];
	minHeapArray[pos2] = temp;
}

template<class T>
int minHeap<T>::capacity() const
{
	return (pow(2, capacityMultiple)-1);
}

template<class T>
bool minHeap<T>::empty() const
{
	return 0 == amountOfElements;
}

template<class T>
bool minHeap<T>::full() const
{
	return size() == capacity();
}

template<class T>
T* minHeap<T>::top() const
{
	if(!empty())
	{
		return minHeapArray[1];
	}

	std::cout << "min-heap array is empty!" << std::endl;

	return 0;
}

template<class T>
void minHeap<T>::push(T *val)
{
	if(full())
	{
		resize();
	}

	//get very last index available
	int index = amountOfElements + 1;
	minHeapArray[index] = val;

	while(index != 1 && *minHeapArray[index] < *minHeapArray[getParentIndex(index)])
	{
		swap(index, getParentIndex(index));
		index = getParentIndex(index);
	}

	amountOfElements +=1;
}

//print used for debugging purposes
template<class T>
void minHeap<T>::print() const
{
	for(int i = 1; i <=capacity(); i++)
	{
		if(minHeapArray[i] !=0)
		{
			std::cout << "NodeVal: " << *minHeapArray[i]; 
		}

		if(minHeapArray[getLeftChildIndex(i)] != 0)
		{
			std::cout <<  ", Leftchild: " << *minHeapArray[getLeftChildIndex(i)];
		}

		if(minHeapArray[getRightChildIndex(i)] != 0)
		{
			std::cout << ", Rightchild: " << *minHeapArray[getRightChildIndex(i)];
		}

		 std::cout<< std::endl;
	}

	std::cout << std::endl;
}
