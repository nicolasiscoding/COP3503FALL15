#include <math.h>
#include <iostream>

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

		//asignment specific			
		// int getSum() const;

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

		// int sum;
};

template<class T>
minHeap<T>::minHeap()
{
	//since 0 is empty, always using (2^n + 1)
	capacityMultiple = 3;
	// sum = 0;

	//initialize minHeapArray to have 3 levels (7 nodes)
	int capacity = pow(2, capacityMultiple);
	minHeapArray = new T*[capacity];

	for (int i = 0; i < capacity; i++)
	{
		minHeapArray[i] = 0;
	}

	amountOfElements = 0;
}

//need to fix
template<class T>
minHeap<T>::~minHeap()
{
	delete minHeapArray;
}

// template<class T>
// int minHeap<T>::getSum() const
// {
// 	return sum;
// }

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

	// //initialize rest to zero
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
	std::cout<< "!!!" << std::endl;
	if(empty())
	{
		std::cout<< "minHeapArray is empty!" << std::endl;
		return;
	}
	// sum-= top();
	T* toDelete = minHeapArray[1];
	std::cout << "First Address" << minHeapArray[1] << std::endl;
	minHeapArray[1] = minHeapArray[amountOfElements];
	minHeapArray[amountOfElements] = 0;
	std::cout << "First Address" << minHeapArray[1] << std::endl;
	std::cout << "Last Address" << minHeapArray[0] << std::endl;
	amountOfElements-=1;

	std::cout<< "Checkpoint 6" << std::endl;
	// std::cout << toDelete << std::endl;
	// delete toDelete;
	std::cout<< "Checkpoint 7.1" << std::endl;
	reheapthearray(1);
}

template<class T>
void minHeap<T>::reheapthearray(int index)
{
	std::cout << "\n\n New iteration of reheap\n" << std::endl;
	// std::cout << "Reheaping" << std::endl;
	// print();
	T *currentNode = minHeapArray[index];

	int leftChildIndex = getLeftChildIndex(index);
	T *leftChild = minHeapArray[leftChildIndex];

	// std::cout<< "Checkpoint 7.2" << std::endl;

	int rightChildIndex = getRightChildIndex(index);
	T *rightChild = minHeapArray[rightChildIndex];

	int smallestValueIndex = -1;

	// std::cout<< "Checkpoint 7.3" << std::endl;

	//debug
		std::cout<< "index: " << index << std::endl;
		std::cout<< "leftChildIndex: " << leftChildIndex << std::endl;
		std::cout<< "rightChildIndex: " << rightChildIndex << std::endl;
		std::cout<< "capacity(): " << capacity() << std::endl;
		std::cout << "leftChild " << leftChild << std::endl;
		std::cout << "rightChild " << rightChild << std::endl;

		if(leftChild != 0)
		{
			std::cout<< "*leftChild: " << *leftChild << std::endl;
		}

		if(rightChild != 0)
		{
			std::cout<< "*rightChild: " << *rightChild << std::endl;
		}

		if(currentNode!= 0)
		{
			std::cout<< "*currentNode " << *currentNode << std::endl;
		}
		std::cout << "size() " << size() << std::endl;



	if(leftChildIndex <= capacity() && leftChild!=0 && *leftChild < *currentNode)
	{
		// std:: cout << "Picking leftChildIndex" << std::endl;
		std::cout<< "Checkpoint 7" << std::endl;
		smallestValueIndex = leftChildIndex;
		currentNode = leftChild;
	}


	
	if(rightChildIndex <= capacity() && rightChild!= 0 && *rightChild < *currentNode)
	{
		// std:: cout << "Picking rightChildIndex" << std::endl;
		std::cout<< "Checkpoint 8" << std::endl;
		smallestValueIndex = rightChildIndex;
	}

	if(smallestValueIndex == -1)
	{
		std::cout<< "Checkpoint 9\n\n" << std::endl;
		return;
	}

	// std::cout <<"startswap" << std::endl;
	swap(index, smallestValueIndex);
	reheapthearray(smallestValueIndex);

}

template<class T>
void minHeap<T>::swap(int pos1, int pos2)
{
	std::cout<< "Checkpoint 10" << std::endl;
	T* temp = minHeapArray[pos1];
	minHeapArray[pos1] = minHeapArray[pos2];
	minHeapArray[pos2] = temp;
	std::cout << "Checkpoint 11" << std::endl;
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
	// if(full())
	// {
	// 	resize();
	// }
	
	//From old implementation without resizing
	if(full())
	{
		std::cout << "min-heap is full!" << std::endl;
		return;
	}

	//get very last index available
	int index = amountOfElements + 1;
	// std::cout << "index of insertion = " << index<< std::endl;

	minHeapArray[index] = val;

	// print();

	while(index != 1 && *minHeapArray[index] < *minHeapArray[getParentIndex(index)])
	{
		// std::cout << "Swapping: " << minHeapArray[index] << " with " << minHeapArray[getParentIndex(index)] << std::endl;
		swap(index, getParentIndex(index));
		index = getParentIndex(index);
	}

	amountOfElements +=1;
	// sum+=val;
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
