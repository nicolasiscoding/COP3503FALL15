#include <iostream>
#include <stdlib.h>
#include "CircleLL.cpp"
using namespace std;

int stringToInt(string str)
{
	int ret = atoi(str.c_str());
	return ret;
}

int main()
{
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
		
		int position;

		//Insert
		if(command[0] == 'I' || command[0] == 'i')
		{
			//remove command information
			command = command.substr(2);
			
			//Find element to insert
			string element = command.substr(0,command.find(' '));
			
			command = command.substr(command.find(' ') + 1);

			//find position to insert to
			position = stringToInt(command);

			LinkedList->Insert(position, element);			
		}
		else if(command[0] == 'D' || command[0] == 'd')
		{
			command = command.substr(2);
			LinkedList->RemoveAtIndex(stringToInt(command));
		}
		//print the element at position i  
		else if(command[0] == 'P' || command[0] == 'p')
		{
			command = command.substr(2);
			position = stringToInt(command);
			LinkedList->PrintAtElement(position);
		}
		//print entire list
		else if(command[0] == 'S' || command[0] == 's')
		{
			LinkedList->PrintLL();
		}
		else if(command[0] == 'J' || command[0] == 'j')
		{
			command = command.substr(2);

			//figure out 'n', or number of inputs before the head
			int numOfInputs = stringToInt(command.substr(0, command.find(' ')));
			//cout << "Num of inputs: "<< numOfInputs<< endl;;

			//move string to next parameters to parse
			command = command.substr(command.find(' ') + 1);

			//parse kth elements to be removed 
			int kElementToBeRemoved = stringToInt(command.substr(0, command.find(' ')));
			//kElementToBeRemoved+= -1; // because the index is always one less then the actual number
			//cout << "Every Kth element will be removed: "<< kElementToBeRemoved<< "\n" << endl;;

			int index = 0;

			//parse and insert at head until the last one 
			while(numOfInputs > 0 && index++ < numOfInputs)
			{
				//move string to next parameters
				command = command.substr(command.find(' ') + 1);
				LinkedList->Insert(0, command.substr(0, command.find(' ')));
			}


			//1 2 3 4 5 6 7 8 //k = 2
			//1 3 5 6 7 8   
			//LinkedList->PrintLL();
			std::stringstream ss;
			ss<< '[';

			//Tell Iterator to go to the beginning position
			LinkedList->toBeginIter();
			//move us to the first position of removal
			for(int i = 0; i < (kElementToBeRemoved - 1); i++)
				{
					LinkedList->moveForward();
				}


			while(LinkedList->size() != 0)
			{

				
				//LinkedList->PrintLL();
				/*cout << "Index to be removed " << index << endl;
				cout << "Element to be removed " << LinkedList->getElementValue(index) << endl;
				ss << LinkedList->getElementValue(index) << ',';
				LinkedList->RemoveAtIndex(index);
				index = index + (kElementToBeRemoved-1);

				if(index > (LinkedList->size()-1))
				{
					index = --startindex;
				}

				*/
				ss << LinkedList->getElementValue(LinkedList->getIterPos()) << ',';
				//removes element at psuedo iterator postion, and moves psuedo iterator by a offset of kElementToBeRemoved
				LinkedList->removeAtIter(kElementToBeRemoved);


			}

			string toPrint = ss.str().substr(0, ss.str().size()-1);
			cout << toPrint << "]" << endl;

		}
		else
		{
			//exception handling redo command
			cout << "Bad input, please redo command";
			i--;
		}
	}

	delete LinkedList;
}