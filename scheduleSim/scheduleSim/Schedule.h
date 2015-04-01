#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "Process.h"
#include <queue>

//add process should do time things like mark when process went into queue and other such things
//that we haven't figured out how to track yet.
class Schedule{
protected:
	std::queue<Process*> q;
	Process *next_process;
public:
	Schedule();
	virtual void add_process(Process*);		
	Process* get_next_process(){
		next_process = q.front();
		q.pop();
		return next_process();	
	}
	bool exist_processes(){
		return !q.empty();
	}
	void_add_process(Process* p);


};

class FCFS: public Schedule{
protected:
	std::queue<Process*> q;
public:
	FCFS();

	void add_process(Process* p){
		p->run_time = p->remaining_burst_time;
		q.push(p);
	}

};

class Round_Robin: public Schedule{
private:
	int time_quantum;
	
public:
	Round_Robin(){
		time_quantum = 1;
	}
		
	Round_Robin(int t){
		time_quantum = t;
	}
	
	void add_process(Process* p){
		p->run_time = p->time_quantum;
		q.push(p);
	}

};

//I might not be able to overload like this --Jenna
class SPN: public Schedule{
private:
	std::priority_queue<Process*> q;
public:

	void add_process(Process* p){
		p->run_time = p->remaining_burst_time;
		q.push(p);
	}
};




#endif
