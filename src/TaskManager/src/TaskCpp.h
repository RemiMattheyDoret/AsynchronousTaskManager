#ifndef TaskCpp_H
#define TaskCpp_H


#include <future>
#include <thread>
#include <condition_variable>
#include <chrono>

#include "TypeDefinitions.h"
#include "Task.h"
#include "CppProcessController.h"

class TaskCpp : public Task
{
	/*
		No need for virtual inheritence, there wno't be diamond problem
		TaskShell is used when a process in defined directly in the shell.
	*/

	public:
		TaskCpp(const function_t fct);
		~TaskCpp();

		/*
			Simply use the constructor to start the Task. There is therefore no start method
			virtual start(std::string& process) = 0;
		*/
		
	
		void pause() override;
		void resume() override;
		void stop() override;
		int status() override;
		

	private:

		std::condition_variable _condVar;
		std::future<bool> _future;
};



#endif /* TaskCpp_H */
