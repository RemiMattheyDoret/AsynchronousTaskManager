#include "CppProcessController.h"
#include <iostream>

CppProcessController::CppProcessController(std::condition_variable& condVar, std::mutex& mu, Task::TaskStatus* statusP, double* progressP)
	:_condVar(condVar), _mu(mu), _statusP(statusP), _progressP(progressP)
	{
		auto l = std::unique_lock<std::mutex>(_mu);
		setProgress(0.0);
	}


bool CppProcessController::pause_and_shouldStop(double progress)
{
	/*
		Is called from TaskCpp to figure out if the process should stop or not. If the status has been set to 'paused', then 'pause_and_shouldStop' will pause
	*/

	auto l = std::unique_lock<std::mutex>(_mu);

	setProgress(progress);

	_condVar.wait(
		l,
		[&]{ return *_statusP == Task::running || *_statusP == Task::stopped || *_statusP == Task::completed; }
	);

	if (*_statusP == Task::stopped || *_statusP == Task::completed)
		return true;
	else
		return false;
}

double CppProcessController::getProgress()
{
	auto l = std::unique_lock<std::mutex>(_mu);
	return *_progressP;
}

void CppProcessController::setProgress(double progress)
{
	// When this function is used, the mutex has already been locked
	*_progressP = progress;
}

