#include "Hardware.h"
#include "Scheduler.h"
#include "Schedule.h"

int main() {
	Hardware h; //create hardware
	Scheduler* s = new Scheduler(); //create scheduler

	//add Schedules to Scheduler
	Round_Robin q1(2); s->add_queue(q1);
	Round_Robin q2(4); s->add_queue(q2);
	Round_Robin q3(8); s->add_queue(q3);
	Round_Robin q4(16); s->add_queue(q4);
	Round_Robin q5(32); s->add_queue(q5);
	FCFS bottom; s->add_queue(bottom);


	h.add_scheduler(s); //add scheduler to hardware
	load_processes("processes.txt", &h); //load processes
	h.simulate(); //run simulation
}