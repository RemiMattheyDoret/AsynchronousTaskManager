#include "Task.h"
#include <iostream>
#include <array>


/*
	Initialize static
*/

unsigned long Task::_currentTaskID = 0; // This thing will be shared among derived class
const std::array<std::string,5> Task::_TaskStatusNames = {"paused", "running", "stopped", "completed", "defaultValue"};




std::unique_lock<std::mutex> Task::lock()
{
	return std::unique_lock<std::mutex>(_mu);
}


void Task::pause()
{
	if (_status == stopped)
		throw std::string("Attempt to pause a process that has already been stopped (killed)\n");

	if (_status == completed)
		throw std::string("Attempt to pause a process that is completed\n");

	if (_status == paused)
		throw std::string("Attempt to pause a process that is already paused\n");

	_status = paused;
		
}

void Task::resume()
{
	if (_status == stopped)
		throw std::string("Attempt to resume a process that has already been stopped (killed)\n");
	
	if (_status == completed)
		throw std::string("Attempt to resume a process that is completed\n");

	if (_status == running)
		throw std::string("Attempt to resume a process that is already running\n");

	_status = running;
}

void Task::stop()
{
	if (_status == stopped)
		throw std::string("Attempt to stop (kill) a process that has already been stopped (killed)\n");

	if (_status == completed)
		throw std::string("Attempt to stop (kill) a process that is completed\n");


	_status = stopped;
}

Task::TaskStatus Task::status()
{
	//std::cout << "\t" << _TaskStatusNames[_status] << "\n";
	return _status;
}

// Constructor will be called from derived classes
Task::Task():_status(running), _taskID(++_currentTaskID){}


// destructor is defined only because it was needed to specify it to be virtual
Task::~Task(){}
