#ifndef CppProcessController_H
#define CppProcessController_H

#include "Task.h"
#include<condition_variable>
#include<mutex>
#include<thread>


class CppProcessController
{
public:
	CppProcessController(std::condition_variable& condVar, std::mutex& mu, Task::TaskStatus* statusP);

	bool pause_and_shouldStop();
	//bool shouldPause();
	
private:
	std::condition_variable& _condVar;
	std::mutex& _mu;
	Task::TaskStatus* _statusP;
};

#endif /* CppProcessController_H */