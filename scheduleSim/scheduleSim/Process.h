#ifndef PROCESS_H
#define PROCESS_H
#include <vector>

enum Status {
	READY,
	RUNNING,
	WAITING_IO,
	IO,
	FINISHED
};

class Process {
public:
	int id;
	int priority;
	std::vector<int> bursts; // array of CPU/IO/CPU/IO... bursts
	Status status;
	int bi; // current burst index
	int remaining_burst_time; // time left in current burst
	int begin_burst_time; // time current burst began running on a core
	int eid; // id of event associated with the process; 
			  // to be removed from event queue if preempted

	Process(int id, int priority, std::vector<int> bursts):
		id(id), priority(priority), bursts(bursts), status(READY), bi(0), remaining_burst_time(bursts[0]), begin_burst_time(0), eid(-1){}
	Process(){
		std::vector<int> b;
		Process(0, 0, b);
	}
};
#endif
