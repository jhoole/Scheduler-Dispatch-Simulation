
#ifndef EVENT_H
#define EVENT_H
#include <vector>

class Hardware;
struct run_request;

class Event{
public:
	int eid;
	int t; // time
	virtual void run(Hardware* h);
	Event(int t) : t(t) {
		static int next_eid = 0;
		eid = next_eid++;
	}
};

class Dispatch_event : public Event {
public:
	int id;
	int priority;
	std::vector<int> bursts; // array of CPU/IO/CPU/IO... bursts
	void run(Hardware* h);
	Dispatch_event(int t, int id, int priority, std::vector<int> bursts) 
		: Event(t), id(id), priority(priority), bursts(bursts) {}
};

class CPUend_event : public Event {
public:
	int pid; // process to move to IO queue
	void run(Hardware* h);
	CPUend_event(int t, int pid) : Event(t), pid(pid){}
};

class IOend_event : public Event {
public:
	int pid;
	void run(Hardware* h);
	IOend_event(int t, int pid) : Event(t), pid(pid) {}
};

class Pause_event : public  Event {
public:
	int pid;
	void run(Hardware* h);
	Pause_event(int t, int pid) : Event(t), pid(pid) {}
};

class Run_event : public Event {
public:
	int pid;
	int core;
	int runtime;
	void run(Hardware* h);
	Run_event(int t, run_request r);
};

class Finish_event : public Event {
public:
	int pid;
	int core;
	int runtime;
	void run(Hardware* h);
	Finish_event(int t, int pid) : Event(t), pid(pid) {}
};

#endif