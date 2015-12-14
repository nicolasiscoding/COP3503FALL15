#include <stack>
#include <queue>
#include "hblt.h"


//Name:				Nicolas Fry
//UF ID:			
//GatorID:			nicolascoding
//Discussion Section: 1085
//Assignment 4
//Kruskals Algorithm with non unionjoin implementation

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
	numNodes = nodes;
	numEdges = edges;

	forestDir1 = new int*[numNodes];
	forestDir2 = new int*[numNodes];
	edgesMinPQ = new hblt<kruskaledge>();

	for(int i = 0; i < numNodes; i++)
	{
		forestDir1[i] = new int[numNodes];
		forestDir2[i] = new int[numNodes];

	}

	for(int i = 0; i < numNodes; i++)
	{
		for(int j = 0; j < numNodes; j++)
		{
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
}

void Kruskals::solve()
{

	if(numNodes == 1)
	{
		return;
	}


	int edgecount = 0;

	while(edgecount != (numNodes-1) && !edgesMinPQ->empty())
	{

		kruskaledge * e = edgesMinPQ->top();

		//in this case, there is more than one way to get to a certain node (that is non-minimum) OR it is a loop to itself 
		if(forestDir1[e->nodeA][e->nodeB] != -1 || forestDir2[e->nodeB][e->nodeA] != -1 || e->nodeA == e->nodeB)
		{
			edgesMinPQ->pop();
			continue;
		}

		//set kruskaledge in forrest
		forestDir1[e->nodeA][e->nodeB] = e->weight;
		forestDir2[e->nodeB][e->nodeA] = e->weight;
		edgecount++;

		//if it causes a cycle, remove kruskaledge
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

	bool ret = recursiveHasCycles(toVisit, hasVisited);

	delete hasVisited;
	delete toVisit;

	return ret;
}

//initialize DFS search to check for cycles
bool Kruskals::recursiveHasCycles(std::stack<int> * toProcess, bool * hasVisited)
{
	if(toProcess->empty())
	{
		return false;
	}

	int next = toProcess->top();
	toProcess->pop();
	hasVisited[next] = true;

	for(int i = 0; i < numNodes; i++)
	{

		if(forestDir1[next][i] != -1 && i != next)
		{
			int check = i;

			if(hasVisited[check])
			{
				return true;
			}

			toProcess->push(check);
		}
	}

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