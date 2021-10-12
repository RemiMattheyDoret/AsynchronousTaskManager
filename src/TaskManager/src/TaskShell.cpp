
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include "TaskShell.h"


bool TaskShell::is_pid_running() const 
{

	/*
		I just copy-pasted the code from https://stackoverflow.com/questions/12601759/determine-if-a-process-exists-from-its-process-id/20240710
	*/

    while(waitpid(-1, 0, WNOHANG) > 0) {
        // Wait for defunct....
    }

    if (0 == kill(_PID, 0))
        return 1; // Process exists

    return 0;
}




TaskShell::TaskShell(const std::string& process)
:Task()
{
	try
	{
		_PID = system2(process.c_str());
	} catch (...)
	{
		std::cerr << "\t\tSome error when startingg the shell process\n";
		std::cerr << "\t\t_PID = " << _PID << "\n";
		std::exit(1);
	}
}

void TaskShell::pause()
{
	auto l = lock();

	Task::pause();

	if (is_pid_running())
		kill(_PID, SIGSTOP);
		//system( ( std::string("kill -TSTP ") + std::to_string(_PID) ).c_str());
}

void TaskShell::resume()
{
	auto l = lock();

	Task::resume();

	if (is_pid_running())
		kill(_PID, SIGCONT);
		//system( ( std::string("kill -CONT ") + std::to_string(_PID) ).c_str());
}

void TaskShell::stop()
{
	auto l = lock();

	Task::stop();

	if (is_pid_running())
		kill(_PID, SIGKILL);
		//system( ( std::string("kill -STOP ") + std::to_string(_PID) ).c_str());
}


Task::TaskStatus TaskShell::status()
{
	auto l = lock();

	// If it thinks it is still running, then make sure that is true or mark it as completed
	if (_status == TaskStatus::running)
	{
		if (!is_pid_running())
		{
			_status = TaskStatus::completed;
		}
	}

	return Task::status();
}

double TaskShell::progress()
{
	throw "A shell task cannot track progress\n";
}


TaskShell::~TaskShell()
{
	if (_status != stopped && _status != completed)
		stop();
}



