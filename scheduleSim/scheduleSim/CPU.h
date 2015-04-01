#ifndef CPU_H
#define CPU_H

class CPU{
private:
	bool state;	//is the CPU running a process or not
	Process* p;	//process running on CPU
public:
	//assign process to CPU
	void assign_process(Process* p){
		this-> p = p;
	}
	
	//somehow track and know when process needs to be let go of, though that might not be this level
	//need to keep track of how long process has been here
	//need to tell process how long it still has left after leaving

};

#endif
