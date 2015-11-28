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
		void solve();
		void print(int &start);
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
		return N1.edges->top() > N2.edges->top();
	}

	friend bool operator<(node &N1, node &N2)
	{
		return N1.edges->top() < N2.edges->top();
	}

	friend bool operator>=(node &N1, node &N2)
	{
		return N1.edges->top() >= N2.edges->top();
	}

	friend bool operator<=(node &N1, node &N2)
	{
		return N1.edges->top() <= N2.edges->top();
	}

	friend bool operator==(node &N1, node &N2)
	{
		return N1.edges->top() == N2.edges->top();
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

	// for(int i = 0; i < numNodes; i++)
	// {
	// 	for(int j = 0; j < numNodes; j++)
	// 	{
	// 		// std::cout << "tp2" << std::endl;
	// 		forest[i][j] = -1;			
	// 	}
	// }
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

	std::cout << "NodeA: " << nodeA << " connects to " << edgeA->connectsTo  << " with weight " << edgeA->weight <<std::endl;

	primsedge * edgeB = new primsedge();
	edgeB->weight = weight;
	edgeB->connectsTo = nodeA;

	std::cout << "NodeB: " << nodeB << " connects to " << edgeB->connectsTo <<  " with weight " << edgeB->weight <<std::endl;


	// forest[nodeA] = edgeB;
	// forest[nodeB] = edgeA;

	if(forest[nodeA] == 0)
	{
		std::cout << "Creating new node at " << nodeA << std::endl;
		node * A = new node();
		A->number = nodeA;
		forest[nodeA] = A;
	}

	if(forest[nodeB] == 0)
	{
		std::cout << "Creating new node at " << nodeB << std::endl;
		node * B = new node();
		B->number = nodeB;
		forest[nodeB] = B;
	}

	forest[nodeA]->edges->push(edgeA);
	std::cout << "Top of node A's edges: " << *forest[nodeA]->edges->top() << std::endl;

	forest[nodeB]->edges->push(edgeB);
	std::cout << "Top of node B's edges: " << *forest[nodeB]->edges->top() << std::endl;

	//debug
	printForest();
}

void Prims::solve()
{

	std::cout << "beginning Prim's solve" << std::endl;
	//if there is one node, it is solved
	if(numNodes == 1)
	{
		return;
	}

	bool hasVisited [numNodes];
	int edgecount = 0;

	//start tree with initial node
	hasVisited[0] = true;
	tree->push(forest[0]);

	// std::cout << *tree->top() << std::endl;

	while(edgecount != (numNodes-1))
	{
		//get the node with the minimum connecting edge weight
		node * current = tree->top();

		//get the minimum edge off the node
		primsedge * leastEdge = current->edges->top();

		std::cout << "minimum node: " << *current << std::endl;
		std::cout << "least edge weight: " << leastEdge->weight << " least edge connecting to " << leastEdge->connectsTo << std::endl;

		//if we have visited the connecting vertex, pop the minimum connecting edge, pop the node from the tree, and
		//reinsert node to tree to get it to find next minimum edge and continue
		if(hasVisited[leastEdge->connectsTo])
		{
			std::cout << "TP1" << std::endl;
			current->edges->pop();
			delete leastEdge;

			tree->pop();
			tree->push(current);
			continue;
		}

		//goes to the node pointer array and get the next node to add
		node * toAdd = forest[leastEdge->connectsTo];

		//push this node into the tree to get the next minimum edge to be on the top
		tree->push(toAdd);

		//visit this node
		hasVisited[leastEdge->connectsTo] = true;

		//start crafting the solution
		PrimSolution p;
		p.nodeA = current->number;
		p.nodeB = toAdd->number;
		p.weight = leastEdge->weight;

		//store solution
		psolution[edgecount] = p;

		//delete edge 
		current->edges->pop();
		delete leastEdge;

		//reinsert current node into tree to recalculate new minimums
		tree->pop();
		tree->push(current);

		edgecount++;
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


//my idea is to have a single vertex node which has several edges (in a min pq). 
//When you find the minimum primsedge, you add the next vertex, and all of it's edges to the MinPQ