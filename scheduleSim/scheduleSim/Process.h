#ifndef PROCESS_H
#define PROCESS_H
#include <vector>

class Process {
public:
	int priority;
	vector<int> bursts; // array of CPU/IO/CPU/IO... bursts
	int bi; // current burst index
	int bt; // used to calculate how much processing time is left
			// while running stores time current burst began
			// while waiting stores time remaining for current burst
	Event* e; // event associated with the process; 
			  // to be removed from event queue if preempted
};
#endif