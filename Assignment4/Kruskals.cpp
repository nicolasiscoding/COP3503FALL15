#include "hblt.cpp"
#include <stack>

//declaring up here because it revoles some issues that are south of this 
struct edge;
class Kruskals
{
	public:
		Kruskals(int nodes, int edges);
		void load(int (&e)[3]);
		void solve();
		void print();
		void printRaw();

	private:
		int numNodes;
		int numEdges;
		int** forest;
		hblt<edge> * edgesMinPQ;

		bool hasCycle(int &startingIndex);
		bool recursiveHasCycles(std::stack<int> * toProcess, bool * visitTracker);
};

struct edge
{
	int weight;
	int nodeA;
	int nodeB;

	friend bool operator>(edge &E1, edge &E2)
	{
		return E1.weight > E2.weight;
	}

	friend bool operator<(edge &E1, edge &E2)
	{
		return E1.weight < E2.weight;
	}

	friend bool operator>=(edge &E1, edge &E2)
	{
		return E1.weight >= E2.weight;
	}

	friend bool operator<=(edge &E1, edge &E2)
	{
		return E1.weight <= E2.weight;
	}

	friend bool operator==(edge &E1, edge &E2)
	{
		return E1.weight == E2.weight;
	}

	friend std::ostream& operator<<(std::ostream &strm, const edge &e)
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
	forest = new int*[numNodes];
	for(int i = 0; i < numNodes; i++)
	{
		forest[i] = new int[numNodes];
	}
	// std::cout << "tp1" << std::endl;
	// forest[1][1] = 9;

	for(int i = 0; i < numNodes; i++)
	{
		for(int j = 0; j < numNodes; j++)
		{
			// std::cout << "tp2" << std::endl;
			forest[i][j] = -1;
		}
	}
}

//pass a three parameter array of Node A, Node B, and Undirectred edge weight respectiely
void Kruskals::load(int (&paramterArr)[3])
{
	//reusing height biased leftist tree from last assignment to impleent min-priority queue
	edgesMinPQ = new hblt<edge>();
	edge * e = new edge();
	e->weight = paramterArr[2];
	e->nodeA = paramterArr[0];
	e->nodeB = paramterArr[1];

	edgesMinPQ->push(e);
	//debug
	// std::cout<< *edges->top() << std::endl;
}

void Kruskals::solve()
{
	//def of spanning tree is (numEdges - 1)
	int edgecount = 0;
	while(edgecount != (numEdges-1) && !edgesMinPQ->empty())
	{
		edge * e = edgesMinPQ->top();

		//in this case, there is more than one way to get to a certain node (that is non-minimum) OR it is a loop to itself 
		if(forest[e->nodeA][e->nodeB] != -1 || forest[e->nodeB][e->nodeA] != -1 || e->nodeA == e->nodeB)
		{
			//the pop function deletes the pointer
			std::cout << "edge connects node to itself OR there is already a minimum value obtained" << std::endl;
			edgesMinPQ->pop();
			continue;
		}

		//set edge in forrest
		forest[e->nodeA][e->nodeB] = e->weight;
		forest[e->nodeB][e->nodeA] = e->weight;
		edgecount++;

		//if it causes a cycle, remove edge
		if(hasCycle(e->nodeA))
		{
			forest[e->nodeA][e->nodeB] = -1;
			forest[e->nodeB][e->nodeA] = -1;
			edgecount--;
		}

		//remove minimum edge from minPQ
		edgesMinPQ->pop();

		printRaw();
		std::cout << "Printed!" << std::endl;
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

	return recursiveHasCycles(toVisit, hasVisited);
}

//initialize DFS search
bool Kruskals::recursiveHasCycles(std::stack<int> * toProcess, bool * hasVisited)
{
	int next = toProcess->top();
	hasVisited[next] = true;
	for(int i = 0; i < numNodes; i++)
	{
		int check = forest[next][i];
		if(check == -1)
		{
			continue;
		}

		if(hasVisited[check])
		{
			return true;
		}

		// toProcess->push(forest[check]);

	}
}

void Kruskals::printRaw()
{
	for(int i = 0; i < numNodes; i++)
	{
		for(int j = 0; j < numNodes; j++)
		{
			std::cout << forest[i][j] << "\t";
		}

		std::cout << std::endl;
	}
}