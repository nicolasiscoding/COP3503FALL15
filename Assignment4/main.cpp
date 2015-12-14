#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <stdlib.h> 
#include "Kruskals.cpp"
#include "Prims.cpp"
#include "BoruvkaSollins.cpp"


//Name:				Nicolas Fry
//UF ID:			
//GatorID:			nicolascoding
//Discussion Section: 1085
//Assignment 4
//Main implementation

//Made with Love, Top Down Design, and Test Driven Development

//toDo
//implement destructor and creation of all dynamic memory

int stringToInt(std::string str)
{
	return atoi(str.c_str());
};

int main()
{
	//params[0] is nodes, params[1] is edges
	int nodes = 0;
	int edges = 0;

	//take input
	std::string inputString;
	std::cout << "Enter number of Nodes and Edges(s):" << std::endl;

	//consider parsing inputs where edges is at LEAST (nodes-1)

	//parse input
	int invalidEntryCount = 1;
	while(true)
	{
		getline(std::cin, inputString);

		if(invalidEntryCount++ > 8)
		{
			std::cout << "Invalid input has been inputted more than 8 times" << std::endl;
			exit(EXIT_FAILURE);
		}

		try
		{
			nodes = stringToInt(inputString.substr(0, inputString.find(' ')));
			edges = stringToInt(inputString.substr(inputString.find(' '))); 			
		}
		catch(const std::out_of_range &e)
		{
			std::cout << "Error, invalid input. edges must be AT LEAST one less than nodes, and you must have AT LEAST 1 node and nodes and edges must be positive" << std::endl;
			continue;
		}
		
		//if edges <= nodes-1, break
		// std::cout << "Edges: " << edges << std::endl;
		// std::cout << "Nodes: " << nodes << std::endl;
		if(nodes-1 <= edges &&  nodes >= 1 && edges >= 0)
		{
			break;
		}

		std::cout << "Error, invalid input. edges must be AT LEAST one less than nodes, and you must have AT LEAST 1 node and nodes and edges must be positive" << std::endl;
	}


	//debug
	// std::cout << params[0] << std::endl;
	// std::cout << params[1] << std::endl;

	//initialize algorithm classes
	Kruskals * k = new Kruskals(nodes, edges);
	BoruvkaSollins * bs = new BoruvkaSollins(nodes, edges);
	Prims * p = new Prims(nodes, edges);

	//iterate through and figure out which nodes connect to each other
	std::cout << "Enter Node A and Node B and Undirected Edge Weights(s):" << std::endl;
	invalidEntryCount = 1;
	for(int i = 0; i < edges; i++)
	{
		if(invalidEntryCount > 8)
		{
			std::cout << "Invalid input has been inputted more than 8 times" << std::endl;
			exit(EXIT_FAILURE);
		}
		//forestDesign[0] is Node A, forestDesign[1] is Node B, forestDesign[2] is undirected edge weight
		int forestDesign [3];
		getline(std::cin, inputString);

		//populate the array of parameters with error handling
		try
		{
			forestDesign[0] = stringToInt(inputString.substr(0, inputString.find(' ')));
			inputString = inputString.substr(inputString.find(' ') +1);
			forestDesign[1] = stringToInt(inputString.substr(0, inputString.find(' ')));
			forestDesign[2] = stringToInt(inputString.substr(inputString.find(' ')));

			// std::cout << forestDesign[0] << std::endl;
			// std::cout << forestDesign[1] << std::endl;
			// std::cout << forestDesign[2] << std::endl;
		}
		catch(const std::out_of_range &e)
		{
			std::cout << "Invalid parameters, plese reenter them again" << std::endl;
			i--;
			invalidEntryCount++;
			continue;
		}

		// if node A > nodes or node B >= nodes then handle this
		if(forestDesign[0] >=  nodes || forestDesign[1] >= nodes)
		{
			std::cout << "You chose invalid node, please reenter parameters with nodes being between 0 and " << nodes-1 << std::endl;
			i--;
			invalidEntryCount++;
			continue;
		}

		k->load(forestDesign);
		p->load(forestDesign);
		bs->load(forestDesign);
	}

	int startNode;
	while(true)
	{
		std::cout << "Enter start Node: " << std::endl;
		getline(std::cin, inputString);

		try
		{
			startNode = stringToInt(inputString);
		}
		catch(const std::out_of_range &e)
		{
			std::cout << "Error, invalid input." << std::endl;
			continue;
		}

		if(startNode >= 0 && startNode < nodes)
		{
			break;
		}
		std::cout << "Error, invalid input. Please input a valid starting point" << std::endl;
	}

	k->solve();
	p->solve(startNode);
	bs->solve();

	k->print();
	std::cout << std::endl;
	p->print();

	delete k;
}
