#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "process.h"
#include "Hardware.h"
#include "Dispatch_event.h"

using namespace std;
/**
 reads in a list of processes to run from a file, 
 and loads those processes into the target process's dispatch queue
*/

void load_processes(string file_name, Hardware *hardware) {
	ifstream f(file_name);
	/* Read in each process */
	string line;
	while (getline(f, line)) {
		istringstream lstream(line);
		Process p;
		Dispatch_event e;
		e.p = p;
		// get dispatch time
		lstream >> e.t;

		// get priority
		lstream >> p.priority;

		// get sequence of CPU/IO times
		int i = 0;
		while (!lstream.eof())
			lstream >> p.bursts[i++];

		// add this to hardware's programs	
		hardware->events.insert(e);
	}
}