
#ifndef PROCESS_H
#define PROCESS_H
#include <vector>

class Event;

enum Status {
	READY,
	RUNNING,
	WAITING_IO,
	IO,
	FINISHED
};

struct Process_history {
	// public stats
	int wait_time;
	int response_time;
	int turnaround_time;
	int context_switches;

	// intermediary stats
	int last_ready_time;
	int dispatch_time;
	Process_history() {
		wait_time = 0;
		response_time = 0;
		turnaround_time = 0;
		context_switches = 0;
		last_ready_time = 0;
		dispatch_time = 0;
	}
};

class Process {
public:
	int id;
	int priority;
	int level; //level of multi level feedback queue
	int time_quantum; //how long running if round robin
	std::vector<int> bursts; // array of CPU/IO/CPU/IO... bursts
	Status status;
	int bi; // current burst index
	int remaining_burst_time; // time left in current burst
	int begin_burst_time; // time current burst began running on a core
	int eid; // id of event associated with the process; 
			  // to be removed from event queue if preempted
	Process_history history;
	

	Process(int id, int priority, std::vector<int> bursts):
		id(id), priority(priority), bursts(bursts), status(READY), bi(0), remaining_burst_time(bursts[0]), begin_burst_time(0), eid(-1), level(0){}
	Process(){
		std::vector<int> b;
		Process(0, 0, b);
	}
	bool operator < (const Process* other){
		return this->remaining_burst_time < other->remaining_burst_time;
	}
};
#endif
