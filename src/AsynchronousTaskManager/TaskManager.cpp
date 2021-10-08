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
		throw std::string("Task with name '") + taskName + std::string("' could not be found. Are you sure you submitted a task with this name previously?\n");
	}

	// Sanity check. This check will be done a second time afterward but I wish to do it here too so that I can figure out where the issue come from shall I experience any issue
	taskID_t taskID = it->second;
	if (taskID >= (taskID_t)tasks.size())
	{
		std::cerr << "taskID " << taskID << " is unknown. This is a bug that was found in function 'findTaskIDFromName'\n";
		std::exit(1);
	}

	return taskID; // return taskID
}

void TaskManager::addTaskToMap(std::string& taskName)
{
	if (NamesIDsmap.size() > 0 && NamesIDsmap.find(taskName) == NamesIDsmap.end())
		throw "Attempt to create a process with an already existing name. All processes must have unique names.\n";
	else
		NamesIDsmap[taskName] = tasks.size();
		
}

void TaskManager::startSHELL(std::string& process, std::string& taskName)
{
	//std::cout << "RUN void TaskManager::startSHELL(std::string& process)\n";
	addTaskToMap(taskName);
	tasks.push_back(new TaskSHELL(process));
}

void TaskManager::startCPP(std::string& process, std::string& taskName)
{
	//std::cout << "RUN void TaskManager::startCPP(std::string& process)\n";
	addTaskToMap(taskName);
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
		throw std::string("taskID ") + std::to_string(taskID) + std::string(" is unknown\n");
}
