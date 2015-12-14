#include <stack>
#include <queue>
#include "hblt.h"
#include  <vector>
#include <algorithm>

//Name:				Nicolas Fry
//UF ID:			
//GatorID:			nicolascoding
//Discussion Section: 1085
//Assignment 4
//Boruvka's Algorithm 

struct BSedge;
struct component;
struct BSsolution;
class BoruvkaSollins
{
	public:
		BoruvkaSollins(int nodes, int edges);
		void load(int (&e)[3]);
		void solve();
		void print();
		void printRaw();
		~BoruvkaSollins();

	private:
		int numNodes;
		int numEdges;


		//initialize a component forrest
		std::vector<component*> queue;

		//store the edges that lead to a solution
		std::vector<BSedge> solution;


		void printForest();
};

struct BSedge
{
	int FromNode;
	int toNode;
	int weight;

	friend bool operator>(BSedge &E1, BSedge &E2)
	{
		return E1.weight > E2.weight;
	}

	friend bool operator<(BSedge &E1, BSedge &E2)
	{
		return E1.weight < E2.weight;
	}

	friend bool operator>=(BSedge &E1, BSedge &E2)
	{
		return E1.weight >= E2.weight;
	}

	friend bool operator<=(BSedge &E1, BSedge &E2)
	{
		return E1.weight <= E2.weight;
	}

	friend bool operator==(BSedge &E1, BSedge &E2)
	{
		if(E1.FromNode == E2.toNode && E1.toNode == E2.FromNode && E1.weight == E2.weight)
			return true;

		return false;
	}

	friend std::ostream& operator<<(std::ostream &strm, const BSedge &e)
	{
  		return strm<< "From: " << e.FromNode << " To: " << e.toNode << " Weight: " << e.weight;
	}
};

struct component
{
	hblt<BSedge> * edges;
	std::vector<int> vertexs;
	bool isEmpty();

	component()
	{
		edges = new hblt<BSedge>();
	}

	~component()
	{
		delete edges;
	}
};

BoruvkaSollins::BoruvkaSollins(int nodes, int edges)
{
	numNodes = nodes;
	numEdges = edges;

	//initialize numNodes many slots for queue
	for(int i = 0; i < nodes; i++)
	{
		queue.push_back(0);
	}
}

void BoruvkaSollins::load(int (&e)[3])
{
	// std::cout << "TP4" << std::endl;
	int weight = e[2];
	int nodeA = e[0];
	int nodeB = e[1];	
	// std::cout << "TP5" << std::endl;

	BSedge * edgeA = new BSedge();
	edgeA->weight = weight;
	edgeA->FromNode = nodeA;
	edgeA->toNode = nodeB;

	BSedge * edgeB = new BSedge();
	edgeB->weight = weight;
	edgeB->FromNode = nodeB;
	edgeB->toNode = nodeA;

	//tests out edge comparison functionality
	// std::cout << "Are they equal? " << (*edgeA == *edgeB) << std::endl;
	// std::cout << "queue[nodeA]: " << queue[nodeA] << " queue[nodeB]: " << queue[nodeB] << std::endl;

	//on loading the forest into queue, it will technically be 1 to 1. 
	if(queue[nodeA] == 0)
	{
		queue[nodeA] = new component();
		queue[nodeA]->vertexs.push_back(nodeA);
	}

	if(queue[nodeB] == 0)
	{
		queue[nodeB] = new component();
		queue[nodeB]->vertexs.push_back(nodeB);
	}

	// std::cout << "queue[nodeA]: " << queue[nodeA] << " queue[nodeB]: " << queue[nodeB] << std::endl;

	queue[nodeA]->edges->push(edgeA);

	queue[nodeB]->edges->push(edgeB);
}

void BoruvkaSollins::print()
{

	std::cout << "BoruvkaSollins's MST:" << std::endl;

	if(numNodes == 1)
	{
		std::cout << "(0)" << std::endl;
		return;
	}

	int totalweight = 0;
	for(int i = 0; i < solution.size(); i++)
	{
		totalweight+=solution[i].weight;
		if(solution[i].toNode <= solution[i].FromNode)
		{
			std::cout << "(" << solution[i].toNode << ", " << solution[i].FromNode << ")" << std::endl;
			continue;
		}

		std::cout << "(" << solution[i].FromNode << ", " << solution[i].toNode << ")" << std::endl;
	}
	std::cout << "Totalweight: " << totalweight << std::endl;
}


void BoruvkaSollins::solve()
{

	while(queue.size() != 1)
	{
		// //temp print queue: UNCOMMENT FOR DEBUG
		// std::cout << "print queue:" << std::endl;
		// for(int i = 0; i < queue.size(); i++)
		// {
		// 	component *print = queue[i];

		// 	std::cout << "Component " << i << ": ";

		// 	for(int j = 0; j < print->vertexs.size(); j++)
		// 	{
		// 		std::cout << (print->vertexs[j]) << ",    ";
		// 	}
		// 	std::cout<<"\n" << std::endl;
		// }
		// std::cout<<"\n" << std::endl;
		// //endtempprint

		//back is technically the first element
		component * front = queue.back();
		BSedge * minEdge = front->edges->top();

		//figure out the node to add to this component
		int connectingTo = minEdge->toNode;
		// std::cout << "BSedge: " << *minEdge << std::endl;

		//pop current minimum edge
		front->edges->pop();

		//Go to second to last node because last node is front
		int componentWithVertexIndex = -1;
		bool found = false;
		for(int i = 0; i < (queue.size()-1); i++)
		{
			//make a temp pointer to check for vertex
			component* toCheck = queue[i];

			for(int j = 0; j < toCheck->vertexs.size(); j++)
			{
				if(toCheck->vertexs[j] == connectingTo)
				{

					//store in solution
					BSedge sol;
					sol.FromNode = minEdge->FromNode;
					sol.toNode = connectingTo;
					sol.weight = minEdge->weight;
					solution.push_back(sol);

					// std::cout << "Found at " << i << std::endl;
					componentWithVertexIndex = i;

					// std::cout << "Popping off top min edge of connecting" << std::endl;
					toCheck->edges->pop();

					found = true;
					break;
				}
			}

			if(found)
			{
				break;
			}
		}

		//once we found the component, we are going to transfer the vertexs and edges to the front component
		if(componentWithVertexIndex == -1)
		{
			std::cout << "\n!!This should never happen!!\n" << std::endl;
			return;
		}

		//This means that this component has the node we are looking for 
		component* temp = queue[componentWithVertexIndex];

		//copy vertexs
		for(int i = 0; i < temp->vertexs.size(); i++)
		{
			// std::cout << "i: " << i << std::endl;
			// std::cout << "temp->vertexs.size()" << temp->vertexs.size()<< std::endl;
			// std::cout << "Pushingback: temp->vertexs[i]: " << temp->vertexs[i] << std::endl;
			front->vertexs.push_back(temp->vertexs[i]);
			// i+=1;
			// std::cout << "i: " << i << std::endl;
			// temp->vertexs.erase(i = )
		}

		//copy edges
		// std::cout << "temp->edges->size()" <<temp->edges->size() << std::endl;
		// std::cout << "temp->edges->top(): " << *(temp->edges->top()) << std::endl;
		for(int i = 0; i < temp->edges->size(); i++)
		{
			BSedge *top = temp->edges->top();
			// std::cout<< "front size:" << front->edges->size() << std::endl;
			// std::cout << "front top:"  << *(front->edges->top()) << std::endl;
			front->edges->push(top);

			// std::cout << "TP3" << std::endl;
			temp->edges->pop();
			// std::cout << "temp->edges->top(): " << *(temp->edges->top()) << std::endl;
			// std::cout << "i = " << i << std::endl;
		}

		//for my eyes only, checking to see if the edges transfered
		// std::cout << "Front edges size: " << front->edges->size() << std::endl;

		//for my eyes only checking to see if vertexs transfered
		// std::cout << "Front vertexs size: " << front->vertexs.size() << std::endl;

		// std::cout << "tp1" << std::endl;

		//remove component that was merged
		queue.erase(queue.begin() + componentWithVertexIndex);

		//pop off back (actually front) and stick in the front (actually the back)
		queue.pop_back();

		//insert in front
		queue.insert(queue.begin(), front);
	}

		// //temp print queue: UNCOMMENT FOR DEBUG
		// std::cout << "print queue:" << std::endl;
		// for(int i = 0; i < queue.size(); i++)
		// {
		// 	component *print = queue[i];

		// 	std::cout << "Component " << i << ": ";

		// 	for(int j = 0; j < print->vertexs.size(); j++)
		// 	{
		// 		std::cout << (print->vertexs[j]) << ",    ";
		// 	}
		// 	std::cout<<"\n" << std::endl;
		// }
		// std::cout<<"\n" << std::endl;
		// //endtempprint
}
