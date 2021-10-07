#include "TaskManager.h"
#include "Task.h"
#include "TaskSHELL.h"
#include "TaskCPP.h"
#include <vector>
#include <unordered_map>
#include <iostream>



TaskManager::~TaskManager()
{
	// Delete all tasks
	for (auto& task : tasks)
	{
		delete task;
	}
}

taskID_t TaskManager::findTaskIDFromName(std::string& taskName)
{
	const auto it = NamesIDsmap.find(taskName);
	if (it == NamesIDsmap.end())
	{
		std::cerr << "Task with name '" << taskName << "' could not be found. Are you sure you submitted a task with this name previously?\n";
		std::exit(1);
	}

	// Sanity check. This check will be done a second time afterward but I wish to do it here too so that I can figure out where the issue come from shall I experience any issue
	taskID_t taskID = it->second;
	if (taskID >= (taskID_t)tasks.size())
	{
		std::cout << "taskID " << taskID << " is unknown. The issue was found in function 'findTaskIDFromName'\n";
	}

	return taskID; // return taskID
}

void TaskManager::startSHELL(std::string& process)
{
	tasks.push_back(new TaskSHELL(process));
}

void TaskManager::startCPP(std::string& process)
{
	tasks.push_back(new TaskCPP(process));
}


void TaskManager::pause(taskID_t taskID)
{
	checkTaskID(taskID);
	tasks[taskID]->pause();
}

void TaskManager::pause(std::string& taskName)
{
	pause(findTaskIDFromName(taskName));
}

void TaskManager::resume(taskID_t taskID)
{
	checkTaskID(taskID);
	tasks[taskID]->resume();
}

void TaskManager::resume(std::string& taskName)
{
	resume(findTaskIDFromName(taskName));
}

void TaskManager::stop(taskID_t taskID)
{
	checkTaskID(taskID);
	tasks[taskID]->stop();
}

void TaskManager::stop(std::string& taskName)
{
	stop(findTaskIDFromName(taskName));
}

void TaskManager::status(taskID_t taskID)
{
	checkTaskID(taskID);
	tasks[taskID]->status();
}

void TaskManager::status(std::string& taskName)
{
	status(findTaskIDFromName(taskName));
}


void TaskManager::checkTaskID(taskID_t& taskID)
{
	if (taskID >= (taskID_t)tasks.size())
	{
		std::cout << "taskID " << taskID << " is unknown\n";
	}
}
