#include <iostream>
#include "Hardware.h"
#include "Scheduler.h"
#include "Schedule.h"

using namespace std;
void averages(Hardware *h){
	double wait_time = 0;
	double response_time = 0;
	double turnaround_time = 0;
	double context_switches = 0;

	Hardware_history hist = h->history;
	int s = hist.processes.size();
	for (int i = 0; i < s; i++){
		wait_time += hist.processes[i]->history.wait_time;
		response_time += hist.processes[i]->history.response_time;
		turnaround_time += hist.processes[i]->history.turnaround_time;
		context_switches += hist.processes[i]->history.context_switches;
	}
	cout << "Averages:\n ----------------\n";
	cout << "Wait time: " << wait_time / s << endl;
	cout << "Response Time:  " << response_time / s << endl;
	cout << "Turnaround Time: " << turnaround_time / s << endl;
	cout << "Context Switches: " << context_switches / s << endl;

	double cpu = 0;
	for (int i = 0; i < N_CORES; i++){
		cpu += hist.core_busy_times[i];
	}
	cout << "CPU Busy Time: " << ((cpu / N_CORES) /h->time) * 100 << "%" << endl;

}

int main() {
	Hardware h; //create hardware
	Scheduler* s = new Scheduler(); //create scheduler

	//add Schedules to Scheduler
	/*Round_Robin* q0 = new Round_Robin(2); s->add_queue(q0);
	Round_Robin* q1 = new Round_Robin(4); s->add_queue(q1);
	Round_Robin* q2 = new Round_Robin(8); s->add_queue(q2);
	Round_Robin* q3 = new Round_Robin(16); s->add_queue(q3);
	Round_Robin* q4 = new Round_Robin(32); s->add_queue(q4);*/
	//FCFS* bottom = new FCFS; s->add_queue(bottom);
	SPN *spn = new SPN; s->add_queue(spn);


	h.add_scheduler(s); //add scheduler to hardware
	load_processes("processes1.txt", &h); //load processes
	h.simulate(); //run simulation
	averages(&h);
}