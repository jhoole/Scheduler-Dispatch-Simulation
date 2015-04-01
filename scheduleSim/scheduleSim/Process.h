#ifndef PROCESS_H
#define PROCESS_H
#include <vector>

class Process {
public:
	int priority;
	std::vector<int> bursts; // array of CPU/IO/CPU/IO... bursts
	int burst_index; // current burst index
	int remaining_burst_time; // used to calculate how much processing time is left
			// while running stores time current burst began
			// while waiting stores time remaining for current burst
	int run_time; //how long the CPU should run the process for --used for Round Robin preemption		
	Event* e; // event associated with the process; 
			  // to be removed from event queue if preempted
	int wait;	//total wait time
	int response; //first response time
	int turnaround; //total turnaround time
	int level; //tracking which level of the feedback queue the process should be inserted into
	
	//what all are we putting directly into the process constructor? --Jenna
	Process();
	
	//trying this for priority queue though I may be misunderstanding the process --Jenna
	bool operator<(const Process*& left, const Process*& right){
		return left->remaining_burst_time < right->remaining_burst_time;
	}
};
#endif
