#include "CppProcessController.h"
#include <iostream>

CppProcessController::CppProcessController(std::condition_variable& condVar, std::mutex& mu, Task::TaskStatus* statusP)
	:_condVar(condVar), _mu(mu), _statusP(statusP)
	{}


bool CppProcessController::pause_and_shouldStop()
{
	auto l = std::unique_lock<std::mutex>(_mu);

	_condVar.wait(
		l,
		[&]{ return *_statusP == Task::running || *_statusP == Task::stopped || *_statusP == Task::completed; }
	);

	if (*_statusP == Task::stopped || *_statusP == Task::completed)
		return true;
	else
		return false;
}


/*
bool CppProcessController::shouldPause()
{
	auto l = std::unique_lock<std::mutex>(_mu);
	std::cout << "line 27\n";
	_condVar.wait(
		l,
		[&]{ return *_statusP != Task::paused; }
	);
	std::cout << "line 32\n";

	if (*_statusP == Task::paused){
		std::cout << "line 35\n";
		return true;
	}
	else
		return false;
}
*/
