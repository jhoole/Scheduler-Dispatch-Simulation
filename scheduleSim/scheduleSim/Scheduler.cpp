#include "Scheduler.h"
#include <vector>

//returns the next process available for processing
	Process* Scheduler::get_next_process(){
		int s = q.size();
		for(int i=0; i<s; i++){
			if(q[i]->exist_processes())
				return q[i]->get_next_process();
				
		}
	}
	
	//inserts a process into the scheduler
	void Scheduler::insert_process(Process* p){
		if(p->level > q.size()-1){
			q[q.size()-1]->add_process(p);
		}
		else{
			q[p->level]->add_process(p);
		}
	}
