#include "TaskManager.h"
#include "Task.h"
#include "TaskShell.h"
#include "TaskCpp.h"
#include "PredefinedCppTasks.h"
#include "assert.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>




TaskManager::TaskManager()
:_hasquitted(false)
{}


void TaskManager::killAllTasks()
{
	// Kill all tasks
	for (auto& task : tasks)
	{
		delete task;
	}

	// empty task vector
	std::vector<Task*>().swap(tasks);

	// Empty hash map
	std::unordered_map<std::string, taskID_t>().swap(NamesIDsmap);
}

TaskManager::~TaskManager()
{
	killAllTasks();
}

taskID_t TaskManager::findTaskIDFromName(const std::string& taskName) const 
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

void TaskManager::addTaskToMap(const std::string& taskName)
{
	if (NamesIDsmap.size() > 0 && NamesIDsmap.find(taskName) != NamesIDsmap.end())
		throw std::string("Attempt to create a process with an already existing name. All processes must have unique names.\n");
	else
		NamesIDsmap[taskName] = tasks.size();
		
}

void TaskManager::startShell(const std::string& taskName, const std::string& process)
{
	addTaskToMap(taskName);
	tasks.push_back(new TaskShell(process));
}

void TaskManager::startCpp(const std::string& taskName, const std::string& functionName, const std::string& filePath)
{	
	/*
		Note that the ordering of the three statements here matter.
	*/

	const auto fct = PredefinedCppTasks::get_fct_from_fctName(functionName);
	addTaskToMap(taskName);
	tasks.push_back(new TaskCpp(fct, filePath));
}


void TaskManager::pause(const taskID_t taskID)
{
	checkTaskID(taskID);
	tasks[taskID]->pause();
}

void TaskManager::pause(const std::string& taskName)
{
	pause(findTaskIDFromName(taskName));
}

void TaskManager::resume(const taskID_t taskID)
{
	checkTaskID(taskID);
	tasks[taskID]->resume();
}

void TaskManager::resume(const std::string& taskName)
{
	resume(findTaskIDFromName(taskName));
}

double TaskManager::progress(const std::string& taskName)
{
	return progress(findTaskIDFromName(taskName));
}

double TaskManager::progress(const taskID_t taskID)
{
	checkTaskID(taskID);
	return tasks[taskID]->progress();
}

void TaskManager::stop(const taskID_t taskID)
{
	checkTaskID(taskID);
	tasks[taskID]->stop();
}

void TaskManager::stop(const std::string& taskName)
{
	stop(findTaskIDFromName(taskName));
}

std::vector<std::pair<std::string, Task::TaskStatus>> TaskManager::status()
{
	return listTasks();
}

Task::TaskStatus TaskManager::status(const taskID_t taskID)
{
	checkTaskID(taskID);
	return tasks[taskID]->status();
}

Task::TaskStatus TaskManager::status(const std::string& taskName)
{
	return status(findTaskIDFromName(taskName));
}


void TaskManager::checkTaskID(const taskID_t& taskID) const
{
	if (taskID >= (taskID_t)tasks.size())
		throw std::string("taskID ") + std::to_string(taskID) + std::string(" is unknown\n");
}




int TaskManager::submit(const std::string& input, bool isSilent)
{
	//// prepare the stream
	std::istringstream iss(input);

	// Basic command (start, stop, pause, resume, quit)
	std::string basic_command;
	if(!(iss >> basic_command))
	{
		// input string is empty. Do not throw an error just return
		return -1;
	}


	// Read the rest and return the Command object
	if (basic_command == "start")
	{
		// Task type
		std::string taskType;
		if (!(iss >> taskType))
			throw incorrectFormatMessage() + startUsage();

		if (taskType != "CPP" && taskType != "SHELL" && taskType != "cpp" && taskType != "shell")
			throw incorrectFormatMessage() + startUsage();
			

		// task name
		std::string taskName;
		if (!(iss >> taskName))
			throw incorrectFormatMessage() + startUsage();

		// task
		if (taskType == "CPP" || taskType == "cpp")
		{
			std::string process;
			if (!(iss >> process))
				throw incorrectFormatMessage() + startUsage();

			std::string filePath;
			iss >> filePath;  // User is allowed to not specify a filePath


			// Test everything was read
			std::string testEmpty;
			if (iss >> testEmpty)
				throw incorrectFormatMessage() + startUsage();
			

			startCpp(taskName, process, filePath);
			return -1;
			
		} else
		{
			assert(taskType == "SHELL" || taskType == "shell");

			std::string process;
			getline(iss, process); // Take whatever is left

			startShell(taskName, process);
			return -1;
		}
			
	} else if (basic_command == "pause")
	{
		// command casual name
		std::string taskName;
		if (!(iss >> taskName))
			throw incorrectFormatMessage() + pauseUsage();


		// Test everything was read
		std::string testEmpty;
		if (iss >> testEmpty)
			throw incorrectFormatMessage() + pauseUsage();

		pause(taskName);
		return -1;

	} else if (basic_command == "resume")
	{
		// command casual name
		std::string taskName;
		if (!(iss >> taskName))
			throw incorrectFormatMessage() + resumeUsage();

		// Test everything was read
		std::string testEmpty;
		if (iss >> testEmpty)
			throw incorrectFormatMessage() + resumeUsage();
		
		resume(taskName);
		return -1;
		
	}  else if (basic_command == "status")
	{
		// command casual name
		std::string taskName;
		iss >> taskName;

		// Test everything was read
		std::string testEmpty;
		if (iss >> testEmpty)
			throw incorrectFormatMessage() + statusUsage();
		
		if (taskName == "")
		{
			std::vector<std::pair<std::string, Task::TaskStatus>> statuses = status();
			
			if (!isSilent)
			{
				// print statuses
				for (auto& elem : statuses)
				{
					// print name
					std::cout << elem.first << ":";

					// print status
					printStatus(elem.second);
			    }
			}

		    return -1;

		} else
		{
			Task::TaskStatus statusValue = status(taskName);
			if (!isSilent) printStatus(statusValue);
			return statusValue;
		}
		
	} else if (basic_command == "stop")
	{
		
		// command casual name
		std::string taskName;
		if (!(iss >> taskName))
			throw incorrectFormatMessage() + stopUsage();

		// Test everything was read
		std::string testEmpty;
		if (iss >> testEmpty)
			throw incorrectFormatMessage() + stopUsage();

		stop(taskName);
		return -1;
	} else if (basic_command == "quit")
	{
		// Test everything was read
		std::string testEmpty;
		if (iss >> testEmpty)
			throw incorrectFormatMessage() + quitUsage();

		quit();
		return -1;

	} else if (basic_command == "progress")
	{
		// command casual name
		std::string taskName;
		if (!(iss >> taskName))
			throw incorrectFormatMessage() + progressUsage();

		// Test everything was read
		std::string testEmpty;
		if (iss >> testEmpty)
			throw incorrectFormatMessage() + progressUsage();

		auto progressValue = progress(taskName);
		
		if (!isSilent)
		{
			if (progressValue < 0) // This is in case we want to implement a CPP task that does not (cannot?) report its progress
				std::cout << "No valid progress to report" << std::endl;  
			else
				std::cout << progressValue * 100 << "%" << std::endl;
		}
			
		return -1;

	} else if (basic_command == "help")
	{
		throw helpInfo(); // Not really an exception per say but that's ok.
	} else
	{
		throw std::string("Received unknown command '") + basic_command + std::string("'. For help, please enter 'help'.\n");// + helpInfo();
	}
}


void TaskManager::printStatus(Task::TaskStatus status)
{
	switch (status)
	{
		case Task::TaskStatus::paused:
			std::cout << "\tpaused" << std::endl;
			break;
		case Task::TaskStatus::running:
			std::cout << "\trunning" << std::endl;
			break;
		case Task::TaskStatus::stopped:
			std::cout << "\tstopped" << std::endl;
			break;
		case Task::TaskStatus::completed:
			std::cout << "\tcompleted" << std::endl;
			break;
		default:
			std::cout << "\tundefined status" << std::endl;
			break;
	}
}


void TaskManager::quit()
{
	killAllTasks();
	_hasquitted = true;
}


std::string TaskManager::incorrectFormatMessage() const
{
	return "Incorrect command format!\n";
}


std::string TaskManager::startUsage() const
{
	return "Start:\tStarts a new process. Usage is 'start <task_type> <task_name> <shell process or functionName and filePath>'. The <task_type> is either 'CPP' (or 'cpp') or 'SHELL' (or 'shell'). For examples: 'start cpp myTask pikachu /Users/remi/test/PikaPika.txt' or 'start shell myOtherTask sleep 10s; echo \"it was a good nap\" >> /Users/remi/test/napFile.txt'\n\n";
}

std::string TaskManager::pauseUsage() const
{
	return "Pause:\tPauses a task. Usage is 'pause <task_name>'.\n\n";
}

std::string TaskManager::statusUsage() const
{
	return "Status:\tChecks status of a task. Usage is 'status <task_name>'. The <task_name> is here optional. In absence of task_name, the status of all classes will be listed\n\n";
}

std::string TaskManager::progressUsage() const
{
	return "Progress:\tChecks progress of a task. Usage is 'progress <task_name>'. Progress only works for CPP tasks.\n\n";
}


std::string TaskManager::stopUsage() const
{
	return "Stop:\tStops a task. Usage is 'stop <task_name>'.\n\n";
}

std::string TaskManager::resumeUsage() const
{
	return "Resume:\tResumes a task. Usage is 'resume <task_name>'.\n\n";
}

std::string TaskManager::quitUsage() const
{
	return "Quit:\tQuits application. Usage is just 'quit', with nothing afterward.\n\n"; // This command quits the application and kill all tasks in doing so. When receiving a SIGINT, the application also kill all processes before quiting. Hence, doing 'command + c' or 'control + c' should be equivalent to typing 'quit'
}


std::string TaskManager::helpInfo() const
{
	return  std::string("\n\n") + std::string("TaskManager is a little tool to manage tasks that are either hard wired in C++ (see the files PredefinedCppTasks.h, PredefinedCppTasks.cpp) or that are expressed directly in Shell script. When starting a task (with C++ hard wired task or a shell task), you need to name it. Then, you can inquire the status of the task and you can chose to pause the task, resume it or stop it at wish.\n\n") + startUsage() + statusUsage() + pauseUsage() + stopUsage() + resumeUsage() + quitUsage() + "\n\nFor more information, please consult the README.md.\n\n";
}

bool TaskManager::hasQuitted() const
{
	return _hasquitted;
}



void TaskManager::printLogo() const
{
	std::cout << "\n\n\n";
	std::cout << "╔════╗    ╔╗ ╔═╗╔═╗\n";
	std::cout << "║╔╗╔╗║    ║║ ║║╚╝║║\n";
	std::cout << "╚╣║║╠╩═╦══╣║╔╣╔╗╔╗╠══╦═╗╔══╦══╦══╦═╗\n";
	std::cout << " ║║║║╔╗║══╣╚╝╣║║║║║╔╗║╔╗╣╔╗║╔╗║║═╣╔╝\n";
	std::cout << " ║║║║╔╗╠══║╔╗╣║║║║║╔╗║║║║╔╗║╚╝║║═╣║\n";
	std::cout << " ╚╚╝╚╝╚╩══╩╝╚╩╝╚╝╚╩╝╚╩╝╚╩╝╚╩═╗╠══╩╝\n";
	std::cout << "                           ╔═╝║\n";
	std::cout << "                           ╚══╝  " << _version << "\n\n\n\n";

}

void TaskManager::printVersion() const
{
	std::cout << _version << std::endl;	
}

void TaskManager::printHelp() const
{
	std::cout << helpInfo();
}

std::vector<std::pair<std::string, Task::TaskStatus>> TaskManager::listTasks(Task::TaskStatus status)
{
	/*
		default status is Task::TaskStatus::defaultValue and mean to just list all tasks
	*/

	std::vector<std::pair<std::string, Task::TaskStatus>> r;
	r.reserve(NamesIDsmap.size());

	for (auto& elem : NamesIDsmap)
	{
		Task::TaskStatus elemStatus = tasks[elem.second]->status();
		auto& elemName = elem.first;
		if (status == Task::TaskStatus::defaultValue || elemStatus == status)
		{
			//std::cout << elemName << ":"; // print name
	    	//std::cout << "\t" << Task::_TaskStatusNames[elemStatus] << "\n";  // print status

	    	r.push_back({elemName, elemStatus});
		}
    }	

    return r;
}
