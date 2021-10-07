#ifndef TASK_H
#define TASK_H

#include<mutex>

#include "TypeDefinitions.h"



/*
	AsynchronousTaskManager::TaskManager::Task have some methods that are pure virtual.
*/

class AsynchronousTaskManager::TaskManager::Task
{
	public:
		enum {paused, running, stopped, completed} TaskStatus;

		// Do not allow constructors or destructors.
		Task() = delete;
		Task(std::string& process) = delete;
		~Task() = delete;
		
		/*
			Simply use the constructor to start the Task. There is therefore no start method
			virtual start(std::string& process) = 0;
		*/


		virtual void pause();
		virtual void resume();
		virtual void stop();

	protected:		
		static unsigned long _currentTaskID = 0; // This thing will be shared among derived class
		TaskStatus _status;
		const unsigned long _taskID;

		std::mutex _mu;
		std::unique_lock<std::mutex> lock();
};



#endif /* TASK_H */

