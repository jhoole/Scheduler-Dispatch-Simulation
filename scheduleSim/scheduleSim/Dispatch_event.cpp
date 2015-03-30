#include "Event.h"
#include "Process.h"
class Dispatch_event : Event {
	Process p;
	void handle(Hardware* h) {
		// TODO: move process into process table
	}
};