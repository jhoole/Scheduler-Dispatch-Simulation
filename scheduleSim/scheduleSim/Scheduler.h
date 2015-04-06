#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <vector>
class Hardware;

struct run_request{
	int pid;
	int core;
	int time;

	run_request(int pid, int core, int time) :
		pid(pid), core(core), time(time){}

	run_request(int pid, int core) :
		pid(pid), core(core), time(-1){}
};

class Scheduler{
public:
	// Looks at current hardware state and requests hardware to 
	// run processes
	// these requests are returned in a vector.
	virtual std::vector<run_request> run(Hardware*) = 0;
};

class FCFS_scheduler : public Scheduler {
public:
	std::vector<run_request> run(Hardware*);
};

#endif