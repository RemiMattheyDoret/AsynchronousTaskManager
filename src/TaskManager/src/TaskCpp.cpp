#include "TaskCpp.h"
#include "PredefinedCppTasks.h"
#include "CppProcessController.h"
#include <iostream>


TaskCpp::TaskCpp(const function_t fct)
:Task()
{
	CppProcessController PC = CppProcessController(  // Process controller.
		_condVar,  // Conditional variable
		_mu,       // Pass the mutex
		&_status
	);

	_future = std::async(std::launch::async, 
		[fct, PC] {
       		fct(const_cast<CppProcessController&&>(PC));  // No idea why PC was considered const here.
       		// it could return anything, it does not matter. The availability of the result is what matter
        	return true; 
    	}
    );
}


void TaskCpp::pause()
{
	{
		auto l = lock();
		Task::pause();
	}
	_condVar.notify_all();
}

void TaskCpp::resume()
{
	{
		auto l = lock();
		Task::resume();
	}
	_condVar.notify_all();
}

void TaskCpp::stop()
{
	{
		auto l = lock();
		Task::stop();
	}
	_condVar.notify_all();
}

Task::TaskStatus TaskCpp::status()
{
	auto l = lock();

	// If it thinks it is still running, then make sure that is true or mark it as completed
	if (_status == TaskStatus::running)
	{
		auto future_status = _future.wait_for(std::chrono::seconds(0));
		
		if (future_status == std::future_status::ready)
		{
			_status = TaskStatus::completed;
		}
	}

	return Task::status();
}


TaskCpp::~TaskCpp()
{
	bool wasAlreadyStoppedorCompleted = true;
	{
		auto l = lock();
		if (_status != stopped && _status != completed)
		{
			wasAlreadyStoppedorCompleted = false;
			Task::stop();
		}
	}
	if (!wasAlreadyStoppedorCompleted)
		_condVar.notify_all();
}

