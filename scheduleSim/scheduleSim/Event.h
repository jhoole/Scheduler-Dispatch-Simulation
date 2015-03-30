#ifndef EVENT_H
#define EVENT_H
class Hardware;

class Event{
public:
	int t;// time
	virtual void handle(Hardware*) = 0;
};

#endif