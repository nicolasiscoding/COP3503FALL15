#include <iostream>
#include <stdlib.h>
#include "CircleLL.cpp"
using namespace std;

//Nicolas Fry
//COP3530
//Assinment 1
//Josephus Problem

int stringToInt(string str)
{
	return atoi(str.c_str());
}

int main()
{https://www.facebook.com/jeffery.zou.1?fref=ts
	//made list a list of strings so user can input whatever they want. 
	CircleLL<string> *LinkedList = new CircleLL<string>();

	
	//take in number of commands
	string numOfCommandsStr;
	getline(cin, numOfCommandsStr);
	int numOfCommands = stringToInt(numOfCommandsStr);

	for(int i = 0; i < numOfCommands;i++)
	{
		//take first command
		string command;
		getline(cin,command);
		
		//Declare position to be used in later statements
		int position;

		//Insert
		if(command[0] == 'I' || command[0] == 'i')
		{
			//remove command information
			command = command.substr(2);
			
			//Find element to insert
			string element = command.substr(0,command.find(' '));
	
			//move string to next parameters to pars
			command = command.substr(command.find(' ') + 1);

			//find position to insert to
			position = stringToInt(command);

			if(position < 0 || position > LinkedList->size())
			{
				cout << "Error: Not a valid position to input." << endl;
				continue;
			}

			LinkedList->Insert(position, element);			
		}

		//Delete
		else if(command[0] == 'D' || command[0] == 'd')
		{
			command = command.substr(2);
			LinkedList->RemoveAtIndex(stringToInt(command));
		}
		
		//Print
		else if(command[0] == 'P' || command[0] == 'p')
		{
			command = command.substr(2);
			position = stringToInt(command);

			if(position > (LinkedList->size()-1) || position < 0)
			{
				cout << "Out of range error" << endl;
				continue;
			}

			LinkedList->PrintAtElement(position);
		}

		//Print Entire List
		else if(command[0] == 'S' || command[0] == 's')
		{
			LinkedList->PrintLL();
		}

		//Josephus
		else if(command[0] == 'J' || command[0] == 'j')
		{
			command = command.substr(2);

			//figure out 'n', or number of inputs before the head
			int numOfInputs = stringToInt(command.substr(0, command.find(' ')));

			//move string to next parameters to parse
			command = command.substr(command.find(' ') + 1);

			//parse kth element to be removed 
			int kthElementToBeRemoved = stringToInt(command.substr(0, command.find(' ')));

			//error handling of kthElement
			if(kthElementToBeRemoved < 1)
			{
				cout << "Error: Kth Element To Be Removed must be greater than or equal to one." << endl;
				continue;
			}

			int index = 0;

			//parse and insert at head until the last one 
			while(numOfInputs > 0 && index++ < numOfInputs)
			{
				//move string to next parameters
				command = command.substr(command.find(' ') + 1);
				LinkedList->Insert(0, command.substr(0, command.find(' ')));
			}

			if(LinkedList->size() == 0)
			{
				LinkedList->PrintLL();
				continue;
			}

			//Declare a string stream  #efficiency
			std::stringstream ss;
			ss<< '[';

			//Tell 'psuedo' Iterator to go to the root position
			LinkedList->toBeginIter();

			//move us to the first kthElemeentToBeRemoved 
			for(int i = 0; i < (kthElementToBeRemoved - 1); i++)
				{
					LinkedList->moveForward();
				}

			//After announcement for leaving last element in list, I included it in the list
			while(LinkedList->size() != 1)
			{
				//DEBUG
				LinkedList->PrintLL();

				//insert Element into stringstream that is about to be removed
				ss << LinkedList->getElementValue(LinkedList->getIterPos()) << ',';

				//removes element at psuedo iterator postion, and moves psuedo iterator by a offset of kthElementToBeRemoved
				LinkedList->removeAtIter(kthElementToBeRemoved);

				//proceed until the last rebel has is standing
			}

			//put last person in output
			ss << LinkedList->getElementValue(LinkedList->getIterPos());

			cout << ss.str() << "]" << endl;
		}

		//input is bad, redo input
		else
		{
			//exception handling 
			cout << "Error: Bad input" << endl;
			continue;
		}
	}

	//program is done, call destructor
	delete LinkedList;
}