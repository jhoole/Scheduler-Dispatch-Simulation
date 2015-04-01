#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "Schedule.h"
#include "Process.h"
#include <vector>
class Hardware;

class Scheduler{
private:
		Hardware* hw;
		std::vector<Schedule> multi_level_feedback_queue;

public:

	//will be overall clock

	Schedule();
	// Looks at current hardware state calls for the hardware
	// to run certain processes
	void what_do(Hardware*);

	//give our multilevel feedback queue layers
	void add_queue(Schedule q){ 
		multi_level_feedback_queue.push_back(q);
	}
	
	//returns the next process available for processing
	Process* get_next_process();
	
	//inserts a process into the scheduler
	void insert_process(Process* p);
};

#endif
