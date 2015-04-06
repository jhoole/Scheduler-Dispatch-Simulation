#include "Hardware.h"

void Hardware::push_event(Event* e) {
	for (int i = 0; i < events.size(); i++) {
		if (events[i]->t > e->t) {
			events.insert(events.begin()+i, e);
			return;
		}
	}
	events.push_back(e);
}

void Hardware::simulate() {
	while (!events.empty()){
		// update time to the next event time
		time = events[0]->t;

		// process all events at that time
		while (!events.empty() && events[0]->t == time) {
			Event* e = events[0];
			events.erase(events.begin());
			e->run(this);
		}

		// ask the scheduler what to do
		std::vector<run_request> requests = scheduler->run(this);

		for (int i = 0; i < requests.size(); i++) {
			Run_event *e = new Run_event(time, requests[i]);
			e->run(this);
		}
	}
}