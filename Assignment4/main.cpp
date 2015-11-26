#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <stdlib.h> 
#include "Kruskals.cpp"

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
	int params [2];

	//take input
	std::string inputString;
	std::cout << "Enter number of Nodes and Edges(s):" << std::endl;

	//parse input
	getline(std::cin, inputString);
	params[0] = stringToInt(inputString.substr(0, inputString.find(' ')));
	params[1] = stringToInt(inputString.substr(inputString.find(' ')));

	//debug
	// std::cout << params[0] << std::endl;
	// std::cout << params[1] << std::endl;

	//initialize algorithm classes
	Kruskals * k = new Kruskals(params[0], params[1]);
	//BoruvkaSollin * bs = new BoruvkaSollin();
	//Prims * p = new Prims();

	//iterate through and figure out which nodes connect to each other
	std::cout << "Enter Node A and Node B and Undirected Edge Weights(s):" << std::endl;
	for(int i = 0; i < params[1]; i++)
	{
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
			continue;
		}

		// if node A > nodes or node B >= nodes then handle this
		if(forestDesign[0] >=  params[0] || forestDesign[1] >= params[0])
		{
			std::cout << "You chose invalid node, please reenter parameters with nodes being between 0 and " << params[0]-1 << std::endl;
			i--;
			continue;
		}

		k->load(forestDesign);
	}

	k->solve();
}
