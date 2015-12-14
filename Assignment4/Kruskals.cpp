#include <stack>
#include <queue>
#include "hblt.h"


//Name:				Nicolas Fry
//UF ID:			
//GatorID:			nicolascoding
//Discussion Section: 1085
//Assignment 4
//Kruskals Algorithm with non unionjoin implementation

//To-Do:
//implement Deletes wherever we pop because I commented out the delete in the HBLTs

struct kruskaledge;
class Kruskals
{
	public:
		Kruskals(int nodes, int edges);
		void load(int (&e)[3]);
		void solve();
		void print();
		void printRaw();
		~Kruskals();

	private:
		int numNodes;
		int numEdges;
		int** forestDir1;
		int** forestDir2;
		hblt<kruskaledge> * edgesMinPQ;

		bool hasCycle(int &startingIndex);
		bool recursiveHasCycles(std::stack<int> * toProcess, bool * visitTracker);
		void printBFS(int &totalweight, std::queue<int> * toProcess, bool* hasVisited);
};

struct kruskaledge
{
	int weight;
	int nodeA;
	int nodeB;

	friend bool operator>(kruskaledge &E1, kruskaledge &E2)
	{
		return E1.weight > E2.weight;
	}

	friend bool operator<(kruskaledge &E1, kruskaledge &E2)
	{
		return E1.weight < E2.weight;
	}

	friend bool operator>=(kruskaledge &E1, kruskaledge &E2)
	{
		return E1.weight >= E2.weight;
	}

	friend bool operator<=(kruskaledge &E1, kruskaledge &E2)
	{
		return E1.weight <= E2.weight;
	}

	friend bool operator==(kruskaledge &E1, kruskaledge &E2)
	{
		return E1.weight == E2.weight;
	}

	friend std::ostream& operator<<(std::ostream &strm, const kruskaledge &e)
	{
  		return strm<<e.weight;
	}
};

Kruskals::Kruskals(int nodes, int edges)
{
	// std::cout << "I am Kruskals!" << std::endl;
	numNodes = nodes;
	numEdges = edges;

	//for sake of mapping, add 1 so all indicies will be mapped easily
	forestDir1 = new int*[numNodes];
	forestDir2 = new int*[numNodes];
	edgesMinPQ = new hblt<kruskaledge>();

	for(int i = 0; i < numNodes; i++)
	{
		forestDir1[i] = new int[numNodes];
		forestDir2[i] = new int[numNodes];

	}
	// std::cout << "tp1" << std::endl;
	// forestDir1[1][1] = 9;

	for(int i = 0; i < numNodes; i++)
	{
		for(int j = 0; j < numNodes; j++)
		{
			// std::cout << "tp2" << std::endl;
			forestDir1[i][j] = -1;
			forestDir2[i][j] = -1;
		}
	}
}

Kruskals::~Kruskals()
{
	for(int i = 0; i < numNodes; i++)
	{
		delete forestDir1[i];
		delete forestDir2[i];
	}

	delete forestDir1;
	delete forestDir2;
	delete edgesMinPQ;
}

//pass a three parameter array of Node A, Node B, and Undirectred kruskaledge weight respectiely
void Kruskals::load(int (&paramterArr)[3])
{
	//reusing height biased leftist tree from last assignment to impleent min-priority queue

	//if the node is pointing to itself forget it
	if (paramterArr[0] == paramterArr[1])
	{
		return;
	}

	kruskaledge * e = new kruskaledge();
	e->weight = paramterArr[2];
	e->nodeA = paramterArr[0];
	e->nodeB = paramterArr[1];

	edgesMinPQ->push(e);
	//debug
	// std::cout<< *edges->top() << std::endl;
}

void Kruskals::solve()
{

	if(numNodes == 1)
	{
		// std::cout << "Just one node? that's it?" << std::endl;
		// int passbyreference = 0;
		// print(passbyreference);
		return;
	}


	int edgecount = 0;
	// std::cout << "Edgecount: " << edgecount << std::endl;
	// std::cout << "numNodes:" << numNodes << std::endl;
	// std::cout << "numEdges: " << numEdges << std::endl;
	// std::cout << "EdgeMINPQ size is: " << edgesMinPQ->size() << std::endl;

	while(edgecount != (numNodes-1) && !edgesMinPQ->empty())
	{

		kruskaledge * e = edgesMinPQ->top();

		//in this case, there is more than one way to get to a certain node (that is non-minimum) OR it is a loop to itself 
		if(forestDir1[e->nodeA][e->nodeB] != -1 || forestDir2[e->nodeB][e->nodeA] != -1 || e->nodeA == e->nodeB)
		{
			//NEED TO IMPLEMENT DELETE
			// std::cout << "kruskaledge connects node to itself OR there is already a minimum value obtained" << std::endl;
			edgesMinPQ->pop();
			continue;
		}

		//set kruskaledge in forrest
		// std::cout << "Setting kruskaledge weight: " << e->weight << std::endl; 
		forestDir1[e->nodeA][e->nodeB] = e->weight;
		forestDir2[e->nodeB][e->nodeA] = e->weight;
		edgecount++;

		//if it causes a cycle, remove kruskaledge
		// printRaw();
		std::cout << "\n" << std::endl;
		if(hasCycle(e->nodeA))
		{
			// std::cout << "hasCycle" << std::endl;
			forestDir1[e->nodeA][e->nodeB] = -1;
			forestDir2[e->nodeB][e->nodeA] = -1;
			edgecount--;
		}
		//remove minimum kruskaledge from minPQ
		edgesMinPQ->pop();

		// printRaw();
		// std::cout << "Printed!" << std::endl;

		// std::cout << "Edgecount: " << edgecount << std::endl;
		// std::cout << "numNodes: "<< numNodes << std::endl;
		// std::cout << "numEdges: " << numEdges << std::endl;
		// std::cout << "EdgeMINPQ size is: " << edgesMinPQ->size() << std::endl;
	}
}

bool Kruskals::hasCycle(int &startingIndex)
{
	bool * hasVisited = new bool[numNodes];

	for(int i = 0; i < numNodes; i++)
	{
		hasVisited[i] = false;
	}

	std::stack<int> * toVisit = new std::stack<int>;
	toVisit->push(startingIndex);

	// std::cout << toVisit->top() << std::endl;

	bool ret = recursiveHasCycles(toVisit, hasVisited);

	delete hasVisited;
	delete toVisit;

	return ret;
}

//initialize DFS search
bool Kruskals::recursiveHasCycles(std::stack<int> * toProcess, bool * hasVisited)
{
	// std::cout << "\n\nIteration of recursion" << std::endl;
	if(toProcess->empty())
	{
		return false;
	}

	int next = toProcess->top();
	toProcess->pop();
	// std::cout << "Next: " << next << std::endl;
	hasVisited[next] = true;

	for(int i = 0; i < numNodes; i++)
	{
		//if there is not a connection, and it is not the same node we just came from then check to see if we visited it, otherwise add it to the stack
		// std::cout << "i: " << i << std::endl; 
		// std:: cout << "forestDir1[next][i]: " << forestDir1[next][i] << std::endl;

		if(forestDir1[next][i] != -1 && i != next)
		{
			int check = i;

			if(hasVisited[check])
			{
				// std::cout << "Returning true!" << std::endl;
				return true;
			}

			// std::cout << "Pushing value " << check << " into stack." << std::endl;
			toProcess->push(check);
		}
	}
	//toProcess->pop();

	recursiveHasCycles(toProcess, hasVisited);
}

void Kruskals::printRaw()
{
	//dir1
	std::cout << "Dir1:" << std::endl;
	for(int i = 0; i < numNodes; i++)
	{
		for(int j = 0; j < numNodes; j++)
		{
			std::cout << forestDir1[i][j] << "\t";
		}

		std::cout << std::endl;
	}

	//dir2
	std::cout << "Dir2:" << std::endl;
	for(int i = 0; i < numNodes; i++)
	{
		for(int j = 0; j < numNodes; j++)
		{
			std::cout << forestDir2[i][j] << "\t";
		}

		std::cout << std::endl;
	}
}

void Kruskals::print()
{
	std::cout << "Kruskal's MST" << std::endl;
	if(numNodes == 1)
	{
		std::cout << "(0)" << std::endl;
	}

	int totalweight= 0;
	for(int i = 0; i < numNodes; i++)
	{
		for(int j = 0; j < numNodes; j++)
		{
			if(forestDir1[i][j] != -1)
			{
				totalweight+= forestDir1[i][j];
				if(i <= j)
				{
					std::cout << "(" << i << ", " << j << ")" << std::endl;
					continue;
				}

				std::cout << "(" << j << ", " << i << ")" << std::endl;
			}
		}
	}
	std::cout << "Totalweight: " << totalweight << std::endl;
}