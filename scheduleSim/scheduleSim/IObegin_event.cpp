#include "Event.h"
class IObegin_event : Event {
	Process* p; // process to move to IO queue
	int core;
	void run(Hardware*) {
		// TODO: move process from core to IO queue
	}
};