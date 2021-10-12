#ifndef CppProcessController_H
#define CppProcessController_H

#include "Task.h"
#include<condition_variable>
#include<mutex>
#include<thread>


class CppProcessController
{
public:
	CppProcessController(std::condition_variable& condVar, std::mutex& mu, Task::TaskStatus* statusP, double* progressP);

	bool pause_and_shouldStop(double progress = -1.0);
	void setProgress(double progress);
	double getProgress();
	
private:
	std::condition_variable& _condVar;
	std::mutex& _mu;
	Task::TaskStatus* _statusP;
	double* _progressP;
};

#endif /* CppProcessController_H */