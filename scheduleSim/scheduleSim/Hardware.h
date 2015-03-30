#ifndef HARDWARE_H
#define HARDWARE_H
#include <vector>
#include <set>
#include <queue>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"

struct eventcomp {
	bool operator() (const Event& lhs, const Event& rhs) const
	{
		return lhs.t<rhs.t;
	}
};

class Hardware {
public:
	std::set<Event, eventcomp> events; // ordered sequence of events
	std::queue<Process*> io_queue; // processes which have made IO request
	Scheduler scheduler;
	int cores[4]; // each core stores a PID, or -1 for idle

	/* remove process from executing on core, save its state,
	   and removes its events from the event queue. */
	void quit_process();

	/* Run a particular process on a particular core for an amount of time. 
	   to run indefinitely, set run_time =  0 */
	void run_process(Process* process, int core, int run_time);
	void run_process(Process* process, int core) {
		run_process(process, core, 0);
	}
	/* main simulation loop */
	void simulate();
};

#endif