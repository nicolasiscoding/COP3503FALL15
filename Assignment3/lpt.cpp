#include "hblt.cpp"
#include "minHeap.cpp"
#include "Machine.cpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

//Name:				Nicolas Fry
//UF ID:			
//GatorID:			nicolascoding
//Discussion Section: 1085
//Assignment 3s
//LPT implementation

int commandlineToString()
{
	std::string str;
	std:: getline (std::cin, str);
	return atoi(str.c_str());
}

struct CompareMachineNumber
{
    inline bool operator() (const Machine& Machine1, const Machine& Machine2)
    {
        return (Machine1.getName() < Machine2.getName());
    }
};

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
		jobsToProcess.push_back(jobTime);
	}

	//sort jobs from largest to smallest order as shown in document
	std::sort(jobsToProcess.begin(), jobsToProcess.end(), std::greater<int>());

	//initialize two min priority queue vessels
	minHeap<Machine>* minHeapScheduler = new minHeap<Machine>();
	hblt<Machine>* hbltScheduler = new hblt<Machine>();
	for(int i = 0; i < numMachines; i ++)
	{
		Machine *m = new Machine();
		Machine *n = new Machine();
		m->setName(i+1);
		n->setName(i+1);
		minHeapScheduler->push(m);
		hbltScheduler->push(n);
	}

	std::chrono::time_point<std::chrono::system_clock> minHeapstart;
	std::chrono::time_point<std::chrono::system_clock> minHeapend;

	std::chrono::time_point<std::chrono::system_clock> hbltstart;
	std::chrono::time_point<std::chrono::system_clock> hbltend;

	//LPT algorithm on minHeap

	minHeapstart = std::chrono::system_clock::now();
	for(int i = 0; i < numJobs; i++)
	{
		Machine* l = minHeapScheduler->top();
		std::cout << *l << std::endl;
		minHeapScheduler->pop();
		l->addJob(jobsToProcess[i]);
		minHeapScheduler->push(l);
	}	
	minHeapend = std::chrono::system_clock::now();

	hbltstart = std::chrono::system_clock::now();
	for(int i = 0; i < numJobs; i++)
	{
		Machine* l = hbltScheduler->top();
		hbltScheduler->pop();
		l->addJob(jobsToProcess[i]);
		hbltScheduler->push(l);
	}
	hbltend = std::chrono::system_clock::now();	

	//Display results of minHeap
	std::cout << "\n\nMin Heap Finishing Time: " << std::endl;
	std::cout << "Schedule:" << std::endl;
	std::vector<Machine> minHeapResults;
	int size = minHeapScheduler->size();
	for(int i = 1; i <= size; i++)
	{
		Machine*l = minHeapScheduler->top();
		minHeapResults.push_back(*l);
		minHeapScheduler->pop();
	}
	std::sort(minHeapResults.begin(), minHeapResults.end(), CompareMachineNumber());
	
	for(int i = 0; i < minHeapResults.size(); i++)
	{
		std::cout<< "Machine " << i+1 << ": ";
		minHeapResults[i].printJobs();
	}
	std::chrono::duration<double> minHeapTime = minHeapend - minHeapstart;
	std::cout<< "Time Eapsed: " << minHeapTime.count() <<std::endl;



	//Display Results of HBLT
	std::cout << "\n\nHeight Biased Leftist Tree Finishing Time: " << std::endl;
	std::cout << "Schedule:" << std::endl;
	std::vector<Machine> hbltResults;
	size = hbltScheduler->size();
	for(int i = 1; i <= size; i++)
	{
		Machine*l = hbltScheduler->top();
		hbltResults.push_back(*l);
		hbltScheduler->pop();
	}
	std::sort(hbltResults.begin(), hbltResults.end(), CompareMachineNumber());
	
	for(int i = 0; i < hbltResults.size(); i++)
	{
		std::cout<< "Machine " << i+1 << ": ";
		hbltResults[i].printJobs();
	}
	std::chrono::duration<double> HBLTtime = hbltend - hbltstart;
	std::cout<< "Time Eapsed: " << HBLTtime.count() <<std::endl;


	// std::cout << "\nEnd of scheduling for hieght biased leftist tree implementation" << std::endl;

	// for(int i = 0; i < minHeapScheduler->size(); i++)
	// {
	// 	std::cout << "Popping top Machine: " << std::endl;
	// 	Machine*l = hbltScheduler->top();
	// 	std::cout << *l << std::endl;
	// 	hbltScheduler->pop();
	// }


	delete minHeapScheduler;
	delete hbltScheduler;
}