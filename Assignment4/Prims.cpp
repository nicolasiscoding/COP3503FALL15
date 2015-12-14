#include <stack>
#include <queue>
#include "hblt.h"

//declaring up here because it revoles some issues that are south of this 

//Name:				Nicolas Fry
//UF ID:			
//GatorID:			nicolascoding
//Discussion Section: 1085
//Assignment 4
//Prims Algorithm with 

struct primsedge;
struct node;
struct PrimSolution;
class Prims
{
	public:
		Prims(int nodes, int edges);
		void load(int (&e)[3]);
		void solve(int &startNode);
		void print();
		void printRaw();
		~Prims();

	private:
		int numNodes;
		int numEdges;

		node** forest;
		hblt<node> * tree;
		PrimSolution * psolution;


		void printForest();
};

struct primsedge
{
	int weight;
	int connectsTo;

	friend bool operator>(primsedge &E1, primsedge &E2)
	{
		return E1.weight > E2.weight;
	}

	friend bool operator<(primsedge &E1, primsedge &E2)
	{
		return E1.weight < E2.weight;
	}

	friend bool operator>=(primsedge &E1, primsedge &E2)
	{
		return E1.weight >= E2.weight;
	}

	friend bool operator<=(primsedge &E1, primsedge &E2)
	{
		return E1.weight <= E2.weight;
	}

	friend bool operator==(primsedge &E1, primsedge &E2)
	{
		return E1.weight == E2.weight;
	}

	friend std::ostream& operator<<(std::ostream &strm, const primsedge &e)
	{
  		return strm<< "Weight: " << e.weight << " connectsTo " << e.connectsTo;
	}
};

struct node
{
	hblt<primsedge> * edges;
	int number;
	bool noMoreEdges;

	node()
	{
		edges = new hblt<primsedge>();
		number = -1;
	}

	~node()
	{
		delete edges;
	}

	//compare to see who has the smallest primsedge
	friend bool operator>(node &N1, node &N2)
	{
		if(N1.edges->top() == 0 || N1.noMoreEdges)
			return 0;

		if(N2.edges->top() == 0 || N2.noMoreEdges)
			return 1;

		return *N1.edges->top() > *N2.edges->top();
	}

	friend bool operator<(node &N1, node &N2)
	{

		if(N1.edges->top() == 0 || N1.noMoreEdges)
			return 1;

		if(N2.edges->top() == 0 || N2.noMoreEdges)
			return 0;

		return *N1.edges->top() < *N2.edges->top();
	}

	friend bool operator>=(node &N1, node &N2)
	{
		if(N1.edges->top() == 0 || N1.noMoreEdges) 
			return 0;

		if(N2.edges->top() == 0 || N2.noMoreEdges)
			return 1;

		return *N1.edges->top() >= *N2.edges->top();
	}

	friend bool operator<=(node &N1, node &N2)
	{
		if(N1.edges->top() == 0 || N1.noMoreEdges)
			return 1;

		if(N2.edges->top() == 0 || N2.noMoreEdges)
			return 0;

		return *N1.edges->top() <= *N2.edges->top();
	}

	friend bool operator==(node &N1, node &N2)
	{
		if(N1.noMoreEdges || N2.noMoreEdges)
			return 0;

		return *N1.edges->top() == *N2.edges->top();
	}

	friend std::ostream& operator<<(std::ostream &strm, const node &e)
	{
  		return strm<<e.number;
	}
};

struct PrimSolution
{
	int nodeA;
	int nodeB;
	int weight;

	friend std::ostream& operator<<(std::ostream &strm, const PrimSolution &e)
	{
		//formatting
		if(e.nodeA <= e.nodeB)
			return strm<< "(" << e.nodeA << ", " << e.nodeB << ")";
  		else
  			return strm<< "(" << e.nodeB << ", " << e.nodeA << ")";
	}
};

Prims::~Prims()
{
	delete psolution;
	delete tree;
	for(int i = 0; i < numNodes; i++)
	{
		delete forest[i];
	}

	delete forest;
}

Prims::Prims(int nodes, int edges)
{
	numNodes = nodes;
	numEdges = edges;

	tree = new hblt<node>();

	forest = new node*[numNodes];
	for(int i = 0; i < numNodes; i++)
	{
		forest[i] = 0;
	}

	psolution = new PrimSolution[numNodes-1];
};

//pass a three parameter array of Node A, Node B, and Undirectred primsedge weight respectiely
void Prims::load(int (&e)[3])
{
	int weight = e[2];
	int nodeA = e[0];
	int nodeB = e[1];

	primsedge * edgeA = new primsedge();
	edgeA->weight = weight;
	edgeA->connectsTo = nodeB;

	primsedge * edgeB = new primsedge();
	edgeB->weight = weight;
	edgeB->connectsTo = nodeA;

	if(forest[nodeA] == 0)
	{
		node * A = new node();
		A->number = nodeA;
		A->noMoreEdges = 0;
		forest[nodeA] = A;
	}

	if(forest[nodeB] == 0)
	{
		node * B = new node();
		B->number = nodeB;
		B->noMoreEdges = 0;
		forest[nodeB] = B;
	}

	forest[nodeA]->edges->push(edgeA);

	forest[nodeB]->edges->push(edgeB);

}

void Prims::solve(int &startNode)
{

	//if there is one node, it is solved
	if(numNodes == 1)
	{
		return;
	}

	bool hasVisited [numNodes];
	for(int i = 0; i < numNodes; i++)
	{
		hasVisited[i] = false;
	}

	int edgecount = 0;

 	//start tree with initial node
	hasVisited[startNode] = true;
	tree->push(forest[startNode]);


	while(edgecount != (numNodes-1))
	{
		node * current = tree->top();

		if(current->edges->empty())
		{
			current->noMoreEdges = true;
			tree->pop();

			continue;
		}

		//get the minimum edge off the node
		primsedge * leastEdge = current->edges->top();

		//if we have visited the connecting vertex, pop the minimum connecting edge, pop the node from the tree, and
		//reinsert node to tree to get it to find next minimum edge and continue
		if(hasVisited[leastEdge->connectsTo])
		{
			// std::cout << "hasVisitedCase" << std::endl;
			current->edges->pop();
			delete leastEdge;

			tree->pop();
			tree->push(current);
			continue;
		}

		node * toAdd = forest[leastEdge->connectsTo];

		hasVisited[leastEdge->connectsTo] = true;

		PrimSolution p;
		p.nodeA = current->number;
		p.nodeB = toAdd->number;
		p.weight = leastEdge->weight;

		psolution[edgecount] = p;

		current->edges->pop();
		delete leastEdge;

		//reinsert current node into tree to recalculate new minimums
		tree->pop();
		tree->push(current);
		edgecount++;

		//push this node into the tree to get the next minimum edge to be on the top
		tree->push(toAdd);
	}
}


void Prims::printForest()
{
	for(int i = 0; i < numNodes; i++)
	{
		if(forest[i] != 0)
		{
			std::cout << "N" << i << "\t";
		}
	}

	std::cout << std::endl;

	for(int i = 0; i < numNodes; i++)
	{	
		if(forest[i] != 0)
		{
			std::cout << *forest[i] << "\t";
		}
	}

	std::cout <<"\n"<< std::endl;
}

void Prims:: print()
{
	std::cout << "Prim's MST:" << std::endl;
	int totalweight = 0;
	if(numNodes == 1)
	{
		std::cout << "(0)" << std::endl;
	}

	for(int i = 0; i < numNodes-1; i++)
	{
		std::cout << psolution[i] << std::endl;
		totalweight += psolution[i].weight;
	}

	std::cout <<  "Totalweight: " << totalweight << std::endl;
}


