#include <math.h>
#include <iostream>

class minHeap
{
	public:
		minHeap();				//done
		~minHeap();				//done
		bool empty() const;			//done
		int size() const;			//done
		void push(int val);			//done
		int top() const;			//done
		void pop();					//done
		int capacity() const;		//done
		bool full() const;			//done
		void print() const;			//done


	private:
		//methods
		int getLeftChildIndex(int index) const;
		int getRightChildIndex(int index) const;
		int getParentIndex(int index) const;
		void resize();
		void reheapthearray(int index);
		void swap(int pos1, int pos2);

		//vars
		int *minHeapArray;
		int amountOfElements;
		int capacityMultiple; 
};

minHeap::minHeap()
{
	//since 0 is empty, always using (2^n + 1)
	capacityMultiple = 3;

	//initialize minHeapArray to have 3 levels (7 nodes)
	int capacity = pow(2, capacityMultiple);
	minHeapArray = new int[capacity];

	for (int i = 0; i < capacity; i++)
	{
		minHeapArray[i] = 0;
	}

	amountOfElements = 0;
}

minHeap::~minHeap()
{
	delete minHeapArray;
}

int minHeap::getLeftChildIndex(int index) const
{
	int cap = capacity();
	if(2 * index > cap)
	{
		return 0;
	}
	return 2 * index;
}

int minHeap::getRightChildIndex(int index) const
{

	int cap = capacity();
	if(2 * index + 1> cap)
	{
		return 0;
	}

	return 2 * index + 1;
}

int minHeap::getParentIndex(int index) const
{
	return index/2;
}

void minHeap::resize() 
{
	//figuring out new capacity and instanciating new array
	int newCapacityMultiple = capacityMultiple + 1;
	int newCapacity = pow(2, newCapacityMultiple);
	int *newArray = new int[newCapacity];

	//figure out old capacity and copy elements to new minHeap Array
	int oldCapacity = pow(2, capacityMultiple);
	for(int i = 0; i <oldCapacity; i++)
	{
		newArray[i] = minHeapArray[i];
	}

	//make new array the minHeap Array
	int *temp = minHeapArray;
	minHeapArray = newArray;
	delete temp;

	//increase the capacity multiple
	capacityMultiple+=1;
}


int minHeap::size() const
{
	return amountOfElements;
}

void minHeap::pop()
{
	minHeapArray[1] = minHeapArray[amountOfElements];
	minHeapArray[amountOfElements] = 0;
	amountOfElements-=1;
	reheapthearray(1);
}

void minHeap::reheapthearray(int index)
{
	std::cout << "Reheaping" << std::endl;
	print();
	int currentNode = minHeapArray[index];

	int leftChildIndex = getLeftChildIndex(index);
	int leftChild = minHeapArray[leftChildIndex];

	int rightChildIndex = getRightChildIndex(index);
	int rightChild = minHeapArray[rightChildIndex];

	int smallestValueIndex = -1;

	if(leftChildIndex <= capacity() && leftChild < currentNode && leftChild != 0)
	{
		std:: cout << "Picking leftChildIndex" << std::endl;
		smallestValueIndex = leftChildIndex;
		currentNode = leftChild;
	}
	
	if(rightChildIndex <= capacity() && rightChild < currentNode && rightChild != 0)
	{
		std:: cout << "Picking rightChildIndex" << std::endl;
		smallestValueIndex = rightChildIndex;
	}

	if(smallestValueIndex == -1)
	{
		return;
	}

	std::cout <<"startswap" << std::endl;
	swap(index, smallestValueIndex);
	reheapthearray(smallestValueIndex);

}

int minHeap::capacity() const
{
	return (pow(2, capacityMultiple)-1);
}

bool minHeap::empty() const
{
	return 0 == amountOfElements;
}

bool minHeap::full() const
{
	return size() == capacity();
}

int minHeap::top() const
{
	if(!empty())
	{
		return minHeapArray[1];
	}

	std::cout << "min-heap array is empty!" << std::endl;

	return 0;
}

void minHeap::push(int val)
{

	/*
	if(full())
	{
		resize();
	}
	*/

	if(full())
	{
		std::cout << "min-heap is full!" << std::endl;
		return;
	}

	//get very last index available
	int index = amountOfElements + 1;
	std::cout << "index of insertion = " << index<< std::endl;

	minHeapArray[index] = val;

	// print();

	while(index != 1 && minHeapArray[index] < minHeapArray[getParentIndex(index)])
	{
		std::cout << "Swapping: " << minHeapArray[index] << " with " << minHeapArray[getParentIndex(index)] << std::endl;
		swap(index, getParentIndex(index));
		index = getParentIndex(index);
	}

	amountOfElements +=1;
}

void minHeap::print() const
{
	for(int i = 1; i <=capacity(); i++)
	{
		std::cout << "NodeVal: " <<minHeapArray[i]; 

		if(minHeapArray[getLeftChildIndex(i)] != 0)
		{
			std::cout <<  ", Leftchild: " << minHeapArray[getLeftChildIndex(i)];
		}

		if(minHeapArray[getRightChildIndex(i)] != 0)
		{
			std::cout << ", Rightchild: " << minHeapArray[getRightChildIndex(i)];
		}

		 std::cout<< std::endl;
	}

	std::cout << std::endl;
}

void minHeap::swap(int pos1, int pos2)
{
	int temp = minHeapArray[pos1];
	minHeapArray[pos1] = minHeapArray[pos2];
	minHeapArray[pos2] = temp;
}

//				1
//	 2				  3
//4		5			6	7