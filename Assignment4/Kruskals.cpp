#include "hblt.cpp"
//declaring up here because it revoles some issues that are south of this 
struct edge;
class Kruskals
{
	public:
		Kruskals(int nodes, int edges);
		void load(int (&e)[3]);
		void solve();
		void print();

	private:
		bool checkIfCycle();
		int numNodes;
		int numEdges;
		int** forest;
		hblt<edge> * edges;
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
	forest = new int*[numNodes+1];
	for(int i = 1; i <= numNodes; i++)
	{
		forest[i] = new int[numNodes+1];
	}
}

//pass a three parameter array of Node A, Node B, and Undirectred edge weight respectiely
void Kruskals::load(int (&paramterArr)[3])
{
	edges = new hblt<edge>();
	edge * e = new edge();
	e->weight = paramterArr[2];
	e->nodeA = paramterArr[0];
	e->nodeB = paramterArr[1];

	edges->push(e);
	//debug
	// std::cout<< *edges->top() << std::endl;
}

void Kruskals::solve()
{

}