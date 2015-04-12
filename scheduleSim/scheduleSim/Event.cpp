
#include <stdexcept>
#include "Event.h"
#include "Hardware.h"

void Event::run(Hardware* h) {
	// add this event to past events queue
	h->history.events.push_back(this);
}

void Dispatch_event::run(Hardware* h){
	// create process from info
	Process* p = new Process(id, priority, bursts);
	p->history.dispatch_time = h->time;
	p->history.last_ready_time = h->time;
	// move process into process table
	h->processes[id] = p;
	//add process to Scheduler
	h->scheduler->insert_process(p->id, h);
	Event::run(h);
}

void CPUend_event::run(Hardware *h)  {
	Process* p = h->processes[pid];
	if (p->status != RUNNING) {
		// TODO: throw error
		throw "process is not in running status";
	}
	bool proc_found = false;
	// set core to -1
	int core;
	for (core = 0; core < N_CORES; core++) {
		if (h->cores[core] == pid) {
			h->cores[core] = -1;
			proc_found = true;
			break;
		}
	}
	if (!proc_found) {
		// TODO: throw error
		throw "process not found to be running on a core";
	}
	
	h->history.core_busy_times[core] += h->time - h->history.core_last_busy_times[core];

	// disassociate process with the CPUend_event
	p->eid = -1;
	// if an IO burst is next
	if (p->bi < p->bursts.size() -1) {
		// update process progress
		p->bi++;
		//set multi level feedback queue return level to 0
		p->level = 0;
		// move to IO queue
		h->io_queue.push(pid);
		// if first in queue:
		if (h->io_queue.size() == 1) {
			// create IOend event and associate it with process
			IOend_event *ioe = new IOend_event(h->time + p->bursts[p->bi], pid);
			p->eid = ioe->eid;
			h->push_event(ioe);
			p->status = IO;
		}
		// else:
		else {
			p->status = WAITING_IO;
		}
	}
	// if the process is finished:
	else {
		Finish_event *fe = new Finish_event(h->time, pid);
		fe->run(h);
	}
	// set status to WAITING_IO
	Event::run(h);
}

void IOend_event::run(Hardware* h) {
	Process* p = h->processes[pid];

	// if the current process isn't at the top of the queue:
	if (h->io_queue.front() != pid) {
		// throw error
		throw "process isn't on top of queue";
	}
	// move process out of IO queue
	h->io_queue.pop();

	// disassociate process from event
	p->eid = -1;

	// if process is unfinished
	if (p->bi < p->bursts.size() - 1) {
		// update process progress
		p->bi++;
		p->remaining_burst_time = p->bursts[p->bi];
		// set status READY
		p->status = READY;
		p->history.last_ready_time = h->time;
		//add back to Scheduler
		h->scheduler->insert_process(p->id, h);
	}
	// if the process is finished:
	else {
		Finish_event *fe = new Finish_event(h->time, pid);
		fe->run(h);
	}

	// start running the next process in the queue
	if (!h->io_queue.empty()) {
		p = h->processes[h->io_queue.front()];
		// create IOend event and associate it with process
		IOend_event *ioe = new IOend_event(h->time + p->bursts[p->bi], p->id);
		p->eid = ioe->eid;
		h->push_event(ioe);
		p->status = IO;
	}

	Event::run(h);
}

void Pause_event::run(Hardware* h)  {
	// TODO: 
	Process *p = h->processes[pid];
	// ensure process state is RUNNING
	if (p->status != RUNNING) {
		throw "process isn't of status RUNNING";
	}
	// find which core process is running on, set that core to -1
	bool proc_found = false;
	// set core to -1
	int core;
	for (core = 0; core < N_CORES; core++) {
		if (h->cores[core] == pid) {
			h->cores[core] = -1;
			proc_found = true;
			break;
		}
	}
	if (!proc_found) {
		// TODO: throw error
		throw "process isn't on a core";
	}
	// set process status to READY
	p->status = READY;
	p->history.last_ready_time = h->time;

	int time_on_core = h->time - h->history.core_last_busy_times[core];
	if (time_on_core > 0)
		h->history.core_busy_times[core] += time_on_core;

	// calculate process remaining burst time
	if (p->begin_burst_time <= h->time)
		p->remaining_burst_time -= h->time - p->begin_burst_time;

	if (p->remaining_burst_time <= 0) {
		// throw error
	}
	Event::run(h);
}

void Run_event::run(Hardware* h) {
	// TODO:
	Process* p = h->processes[pid];
	// make sure process state is READY
	if (p->status != READY) {
		// throw error
		throw "process isn't ready";
	}

	// if a process is already on core:
	if (h->cores[core] != -1) {
		Process* p2 = h->processes[h->cores[core]];
		// find event in queue associated with process on that core
		bool eid_found = false;
		for (int i = 0; i < h->events.size(); i++) {
			if (h->events[i]->eid == p->eid) {
				eid_found = true;
				// delete that event, since it will never happen
				delete h->events[i];
				h->events.erase(h->events.begin() + i);
				break;
			}
		}
		if (!eid_found)
			throw "eid could not be found!";

		// pause the process on that core
		Pause_event* pe = new Pause_event(h->time, h->cores[core]);
		pe->run(h);
	}
	// put process on core
	h->cores[core] = pid;
	// set process status to RUNNING
	p->status = RUNNING;

	// keep track of statistics
	p->history.context_switches++;
	p->history.wait_time += h->time - p->history.last_ready_time;
	if (p->history.dispatch_time == p->history.last_ready_time) {
		p->history.response_time = h->time - p->history.dispatch_time;
	}

	h->history.core_last_busy_times[core] = h->time+CONTEXT_SWITCH_TIME;

	// set begin burst time to current time + context switch time
	p->begin_burst_time = h->time + CONTEXT_SWITCH_TIME;

	// figure out what will happen next to the process
	Event* next_event;
	// if burst time longer than runtime and runtime > -1:
	if (p->remaining_burst_time > runtime && runtime > -1) {
		// add Pause event
		next_event = new Pause_event(p->begin_burst_time + runtime, pid);
		
	}
	else {
		// add cpu-end event
		next_event = new CPUend_event(p->begin_burst_time + p->remaining_burst_time, pid);
	}
	p->eid = next_event->eid;
	h->push_event(next_event);
	Event::run(h);
}

Run_event::Run_event(int t, run_request r) : Event(t) {
	pid = r.pid;
	core = r.core;
	runtime = r.time;
}

void Finish_event::run(Hardware* h) {
	Process* p = h->processes[pid];
	p->status = FINISHED;
	p->history.turnaround_time = h->time - p->history.dispatch_time;
	// move from processes to finished_processes map
	h->history.processes[pid] = p;
	// remove from the running processes map
	h->processes.erase(h->processes.find(pid));
	Event::run(h);
}