#ifndef SCHEDULER_H
#define SCHEDULER_H
class Hardware;

class Scheduler{
	// Looks at current hardware state calls for the hardware
	// to run certain processes
	virtual void run(Hardware*);
};

#endif