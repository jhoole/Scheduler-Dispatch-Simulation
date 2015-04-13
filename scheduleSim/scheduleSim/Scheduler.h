#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Schedule.h"
#include "Process.h"
#include <vector>
#include <queue>
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
private:
	int next_process;
	int time;
	std::vector<Schedule*> mlfq;
public:
	// Looks at current hardware state and requests hardware to 
	// run processes
	// these requests are returned in a vector.
	Scheduler(){
		next_process = -1;
		time = -1;
	}
	std::vector<run_request> run(Hardware*);
	void add_queue(Schedule *q){
		mlfq.push_back(q);
	}
	void get_next_process();
	void insert_process(int p, Hardware* h);
};


#endif
