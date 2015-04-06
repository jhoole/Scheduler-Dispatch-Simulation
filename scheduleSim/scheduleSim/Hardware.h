#ifndef HARDWARE_H
#define HARDWARE_H
#include <vector>
#include <queue>
#include <map>
#include <string>
#include "Process.h"
#include "Event.h"
#include "Scheduler.h"

#define N_CORES 4
#define CONTEXT_SWITCH_TIME 2

class Hardware {
public:
	int time; // current time into the simulation
	std::vector<Event*> events; // ordered sequence of events
	std::vector<Event*> past_events; // log events which have occurred
	std::map<int, Process*> processes; // unfinished processes
	std::map<int, Process*> finished_processes; // for logging purposes
	std::queue<int> io_queue; // processes which have made IO request
	Scheduler* scheduler;
	int cores[N_CORES]; // stores id of process it's running, or -1

	/* Add an event to the event queue in the proper order */
	void push_event(Event* e);

	/* main simulation loop */
	void simulate();

	Hardware() {
		for (int i = 0; i < N_CORES; i++)
			cores[i] = -1;
	}
};
void load_processes(std::string file_name, Hardware *h);
#endif