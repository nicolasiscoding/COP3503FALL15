#include <vector>
#include <sstream>
#include <stdlib.h>
#include <string>

class Machine
{
	public:
		Machine();
		void setName(int n);
		int getName();
		// ~Machine();
		int getTotalTime() const;
		std::vector<int> getJobList() const;
		void addJob(int time);
		void printJobs() const;
		friend std::ostream& operator<<(std::ostream &strm, const Machine &m);

		//comparison
		friend bool operator>(Machine &M1, Machine &M2);
		friend bool operator<(Machine &M1, Machine &M2);
		friend bool operator>=(Machine &M1, Machine &M2);
		friend bool operator<=(Machine &M1, Machine &M2);
		friend bool operator==(Machine &M1, Machine &M2);

	private:
		int jobTimeTotal;
		std::vector<int> jobList;
		int number;

};

void Machine::setName(int n)
{
	number = n;
}

int Machine::getName()
{
	return number;
}

Machine::Machine()
{
	number = 0;
	jobTimeTotal = 0;
}

void Machine::addJob(int time)
{
	jobTimeTotal+=time;
	jobList.push_back(time);
}

std::vector<int> Machine::getJobList() const
{
	return jobList;
}

int Machine::getTotalTime() const
{
	return jobTimeTotal;
}

void Machine::printJobs() const
{
	
	std::stringstream ss;

	std::vector<int> jobs = getJobList();

	std::vector<int>::reverse_iterator i = jobs.rbegin();
	for (; i != jobs.rend(); ++i )
	{
		ss <<  *i << ", ";
	} 
  	
  	std::cout << ss.str().substr(0, ss.str().size()-2)<< std::endl;	
}

std::ostream& operator<<(std::ostream &strm, const Machine &m)
{
  	return strm<<m.getTotalTime();
}

bool operator>(Machine &M1, Machine &M2)
{
	return M1.getTotalTime() > M2.getTotalTime();
}

bool operator<(Machine &M1, Machine &M2)
{
	return M1.getTotalTime() < M2.getTotalTime();
}

bool operator>=(Machine &M1, Machine &M2)
{
	return M1.getTotalTime() >= M2.getTotalTime();
}

bool operator<=(Machine &M1, Machine &M2)
{
	return M1.getTotalTime() <= M2.getTotalTime();
}

bool operator==(Machine &M1, Machine &M2)
{
	return M1.getTotalTime() == M2.getTotalTime();
}

