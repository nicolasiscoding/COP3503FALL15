#include "hblt.cpp"
#include "minHeap.cpp"
#include "Machine.cpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

int commandlineToString()
{
	std::string str;
	std:: getline (std::cin, str);
	return atoi(str.c_str());
}

int main()
{
	std::cout << "Enter number of job(s)" << std::endl;
	int numJobs = commandlineToString();
	if(numJobs < 1)
	{
		std::cout << "\nNot a valid input" << std::endl;
		return -1;
	}

	std::cout << "Enter number of Machine(s)" << std::endl;
	int numMachines = commandlineToString();
	if (numMachines<1)
	{
		std::cout << "\nIf we do not have machines, there is nothing to schedule" << std::endl;
		return -1;
	}

	std::vector<int> jobsToProcess;
	std::cout << "Enter Processing Time(s)" << std::endl;

	for(int i = 0; i < numJobs; i++)
	{
		int jobTime = commandlineToString();
		if(jobTime < 1)
		{
			std::cout << "\nPlease re-enter a time greater than one" << std::endl;
			i--;
			continue;
		}
		std::cout<< jobTime << std::endl;
		jobsToProcess.push_back(jobTime);
	}

	std::sort(jobsToProcess.begin(), jobsToProcess.end(), std::greater<int>());

	std::cout<< jobsToProcess[0] << " " << jobsToProcess[1] << std::endl;

	// std::cout<<"Checkpoint 2" << std::endl;
	minHeap<Machine>* minHeapScheduler = new minHeap<Machine>();
	hblt<Machine>* hbltScheduler = new hblt<Machine>();

	for(int i = 0; i < numMachines; i ++)
	{
		std::cout<<"Creating new machine" << std::endl;
		Machine *m = new Machine();
		m->setName(i+1);
		std::cout<<"Pushing new machine" << std::endl;
		minHeapScheduler->push(m);
		std::cout << "top: " << *minHeapScheduler->top() << std::endl;
	}

	// for(int i = 0; i < numMachines; i++)
	// {
	//  	Machine *m = new Machine();
	// 	m.setName(i+1);
	// // 	hbltScheduler->push(m);
	// }

	// std::cout<<"Checkpoint 4" << std::endl;


	//MinHeap: insert start time here

	std::cout << "jobs: " << std::endl;
	for(int i = 0; i < jobsToProcess.size(); i++)
	{
		std::cout << "\t" << jobsToProcess[i] << std::endl;
	}

	for(int i = 0; i < numJobs; i++)
	{
		std::cout <<"\nStarting iteration of insert loop" << std::endl;
		Machine* l = minHeapScheduler->top();
		std::cout <<"Top: " << *l << std::endl;
		minHeapScheduler->pop();
		std::cout<< "Inserting " << jobsToProcess[i] << " into machine that was previously "<< *l <<std::endl;
		l->addJob(jobsToProcess[i]);
		std::cout<< "New machine value is: " << *l << std::endl;
		minHeapScheduler->push(l);
		std::cout<< "Endloop: new top: " << *minHeapScheduler->top() << std::endl;
	}

	std::cout << "\n\nEnd of scheduling: " << std::endl;
	minHeapScheduler->print();

	for(int i = 0; i < minHeapScheduler->size(); i++)
	{
		std::cout << "Popping top Machine: " << std::endl;
		Machine*l = minHeapScheduler->top();

		std::cout << *l << std::endl;
		minHeapScheduler->pop();
	}


}