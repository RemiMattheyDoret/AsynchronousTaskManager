#ifndef TASKSHELL_H
#define TASKSHELL_H

#include "TypeDefinitions.h"
#include "Task.h"
#include "system2.h"


class TaskShell : public Task
{
	/*
		No need for virtual inheritence, there wno't be diamond problem
		TaskShell is used when a process in defined directly in the shell.
	*/

	public:
		TaskShell(const std::string& process);
		~TaskShell();
		
		/*
			Simply use the constructor to start the Task. There is therefore no start method
			virtual start(std::string& process) = 0;
		*/
		
		void pause() override;
		void resume() override;
		void stop() override;
		Task::TaskStatus status() override;
		double progress() override;

	private:
		bool is_pid_running() const;
		PID_t _PID;
};


#endif /* TASKSHELL_H */