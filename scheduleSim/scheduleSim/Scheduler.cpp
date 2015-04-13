#include "Hardware.h"
#include "Scheduler.h"
#include <vector>

//sets the pID and time quantum of the next process available for processing
void Scheduler::get_next_process(){
	int s = mlfq.size();
	for (int i = 0; i < s; i++){
		if (mlfq[i]->exist_processes()){
			next_process = mlfq[i]->get_next_process();
			time = mlfq[i]->get_time();
			return;
		}	
	}
	next_process = -1;
	time = -1;
}

//inserts the process at the proper level of the multi level feedback queue
void Scheduler::insert_process(int p, Hardware * h){
	if (h->processes[p]->level > h->processes[p]->priority){
		h->processes[p]->level = h->processes[p]->priority;
	}
	if (h->processes[p]->level > mlfq.size())
		mlfq[mlfq.size() - 1]->add_process(p);
	else
		mlfq[h->processes[p]->level]->add_process(p);
}

std::vector<run_request> Scheduler::run(Hardware* h){
	std::vector<run_request> requests;

	//for each core
	for (int i = 0; i < N_CORES; i++){
		//if the core is idle
		if (h->cores[i] == -1){
			get_next_process();
			if (next_process != -1){
				run_request r(next_process, i, time);
				requests.push_back(r);
				h->processes[next_process]->level++; //when the process returns to the queue, it will be sent to a lower level
			}
		}
	}
	return requests;
}