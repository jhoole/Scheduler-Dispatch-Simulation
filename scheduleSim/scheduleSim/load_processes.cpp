#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "process.h"
#include "Hardware.h"
#include "Event.h"

using namespace std;
/**
 reads in a list of processes to run from a file, 
 and adds a dispatch event for each one
*/
void load_processes(string file_name, Hardware *h) {
	// TODO:
	// open process file:
	ifstream processes_file(file_name);
	string line;
	// for each line in file:
	while (getline(processes_file, line)) {
		istringstream lstream(line);
		
		// get process id, dispatch time, priority, cpu/io sequence
		int pid, dt, priority;
		vector<int> bursts;

		lstream >> pid >> dt >> priority;
		int burst;
		while (lstream >> burst)
			bursts.push_back(burst);

		// initialize new dispatch event
		Dispatch_event* de = new Dispatch_event(dt, pid, priority, bursts);
		// add dispatch event to hardware's event queue
		h->push_event(de);
	}
}