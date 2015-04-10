#include "Hardware.h"
#include "scheduler.h"

int main() {
	Hardware h;
	Scheduler* s;
	h.scheduler = s;
	load_processes("processes.txt", &h);
	h.simulate();
}