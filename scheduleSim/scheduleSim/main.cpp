#include "Hardware.h"
#include "scheduler.h"

int main() {
	Hardware h;
	h.scheduler = new FCFS_scheduler();
	load_processes("processes.txt", &h);
	h.simulate();
}