#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "Process.h"
#include <queue>

//add process should do time things like mark when process went into queue and other such things
//that we haven't figured out how to track yet.
class Schedule{
protected:
	std::queue<int> q;
	int next_process;
	int time;
public:
	Schedule() {
		time = -1;
	};

	int get_next_process(){
		next_process = q.front();
		q.pop();
		return next_process;
	}

	bool exist_processes(){
		return !q.empty();
	}

	void add_process(int p){
		q.push(p);
	}

	int get_time(){
		return time;
	}

};

class FCFS : public Schedule{
public:
	FCFS(){
	}
};

class Round_Robin : public Schedule{

public:
	Round_Robin(){
		time = -1;
	}

	Round_Robin(int t){
		time = t;
	}
};

//I might not be able to overload like this --Jenna
class SPN : public Schedule{
private:
	std::priority_queue<int> q;
public:

};

#endif