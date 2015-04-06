#include "Hardware.h"
#include "Scheduler.h"

using namespace std;
vector<run_request> FCFS_scheduler::run(Hardware* h) {
	// make vector for run requests
	vector<run_request> requests;
	// for each core:
	for (int i = 0; i < N_CORES; i++){
		// if core is idle:
		if (h->cores[i] == -1){
			// get next ready process from hardware
			int next_ready_proc = -1;
			for (auto itr = h->processes.begin(); itr != h->processes.end(); itr++) {
				// make sure process isn't already being requested to run on different core
				bool already_requested = false;
				for (int j = 0; j < requests.size(); j++) {
					if (requests[j].pid == itr->second->id) {
						already_requested = true;
						break;
					}
				}
				if (!already_requested && itr->second->status == READY) {
					next_ready_proc = itr->first;
					break;
				}
			}
			// if no process found, then skip
			if (next_ready_proc == -1) break;
			// otherwise add process to run requests
			else {
				run_request r(next_ready_proc, i);
				requests.push_back(r);
			}
		}
	}
	return requests;
}