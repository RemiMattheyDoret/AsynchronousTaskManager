#include "TaskManager.h"
#include "Task.h"
#include "TaskSHELL.h"
#include "TaskCPP.h"
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
	if (NamesIDsmap.size() > 0 && NamesIDsmap.find(taskName) == NamesIDsmap.end())
		throw std::string("Attempt to create a process with an already existing name. All processes must have unique names.\n");
	else
		NamesIDsmap[taskName] = tasks.size();
		
}

void TaskManager::startSHELL(const std::string& process, const std::string& taskName)
{
	//std::cout << "RUN void TaskManager::startSHELL(std::string& process)\n";
	addTaskToMap(taskName);
	tasks.push_back(new TaskSHELL(process));
}

void TaskManager::startCPP(const std::string& process, const std::string& taskName)
{
	//std::cout << "RUN void TaskManager::startCPP(std::string& process)\n";
	addTaskToMap(taskName);
	tasks.push_back(new TaskCPP(process));
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

void TaskManager::stop(const taskID_t taskID)
{
	checkTaskID(taskID);
	tasks[taskID]->stop();
}

void TaskManager::stop(const std::string& taskName)
{
	stop(findTaskIDFromName(taskName));
}

void TaskManager::status()
{
	for (auto& it : NamesIDsmap)
	{
    	std::cout << it.first << ": "; // print name
    	tasks[it.second]->status();    // print status
    }
}

int TaskManager::status(const taskID_t taskID)
{
	checkTaskID(taskID);
	return tasks[taskID]->status();
}

int TaskManager::status(const std::string& taskName)
{
	return status(findTaskIDFromName(taskName));
}


void TaskManager::checkTaskID(const taskID_t& taskID) const
{
	if (taskID >= (taskID_t)tasks.size())
		throw std::string("taskID ") + std::to_string(taskID) + std::string(" is unknown\n");
}




int TaskManager::submit(const std::string& input)
{
	//// prepare the stream
	std::istringstream iss(input);

	// Basic command (start, stop, pause, resume, quit)
	std::string basic_command;
	iss >> basic_command;


	// Read the rest and return the Command object
	if (basic_command == "start")
	{
		// Task type
		std::string taskType;
		if (!(iss >> taskType))
			throw startUsage();

		if (taskType != "CPP" && taskType != "SHELL")
			throw startUsage();
			

		// task name
		std::string taskName;
		if (!(iss >> taskName))
			throw startUsage();

		// task
		if (taskType == "CPP")
		{
			std::string process;
			if (!(iss >> process))
				throw startUsage();


			// Test everything was read
			std::string testEmpty;
			if (iss >> testEmpty)
				throw startUsage();
			

			return submit(
				BaseCommand::START,   // baseCommand
				TaskType::CPP,  	  // taskType
				taskName,             // taskName
				process               // process
			);
			
		} else
		{
			std::string process;
			getline(iss, process); // Take whatever is left


			return submit(
				BaseCommand::START,   	// baseCommand
				TaskType::SHELL,  		// taskType
				taskName,              	// taskName
				process                 // task
			);
		}
			
	} else if (basic_command == "pause")
	{
		// command casual name
		std::string taskName;
		if (!(iss >> taskName))
			pauseUsage();


		// Test everything was read
		std::string testEmpty;
		if (iss >> testEmpty)
			pauseUsage();

		return submit(
			BaseCommand::PAUSE,		// baseCommand
			TaskType::UNKNOWN,  	// taskType
			taskName,               // taskName
			""                      // process
		);

	} else if (basic_command == "resume")
	{
		// command casual name
		std::string taskName;
		if (!(iss >> taskName))
			resumeUsage();

		// Test everything was read
		std::string testEmpty;
		if (iss >> testEmpty)
			resumeUsage();
		
		return submit(
			BaseCommand::RESUME,  	// baseCommand
			TaskType::UNKNOWN,  	// taskType
			taskName,               // taskName
			""                      // process
		);
	}  else if (basic_command == "status")
	{
		// command casual name
		std::string taskName;
		iss >> taskName;

		// Test everything was read
		std::string testEmpty;
		if (iss >> testEmpty)
			statusUsage();
		
		return submit(
			BaseCommand::STATUS,  	// baseCommand
			TaskType::UNKNOWN,  	// taskType
			taskName,               // taskName
			""                      // process
		);
	} else if (basic_command == "stop")
	{
		
		// command casual name
		std::string taskName;
			stopUsage();

		// Test everything was read
		std::string testEmpty;
		if (iss >> testEmpty)
			stopUsage();

		return submit(
			BaseCommand::STOP,		// baseCommand
			TaskType::UNKNOWN,  	// taskType
			taskName,               // taskName
			""                      // process
		);
	} else if (basic_command == "quit")
	{
		// command casual name
		std::string taskName;
		if (!(iss >> taskName))
			quitUsage();

		// Test everything was read
		std::string testEmpty;
		if (iss >> testEmpty)
			quitUsage();

		return submit(
			BaseCommand::QUIT,		// baseCommand
			TaskType::UNKNOWN,		// taskType
			taskName,               // taskName
			""                    	// task
		);
	} else if (basic_command == "help")
	{
		throw helpInfo(); // Not really an exception per say but that's ok.
	} else
	{
		throw std::string("Received unknown command ") + basic_command + std::string(".\n") + helpInfo();
	}
}



int TaskManager::submit(
	const BaseCommand baseCommand,  // start, resume, pause, stop, quit
	const TaskType taskType,  	   	// CPP or SHELL
	const std::string& taskName,    // Casual name to refer to this task
	const std::string& process     	// Name of CPP function or full Shell process
)
{
	int varToReturn = -1; // Only used with status for a single task name

	switch(baseCommand)
	{
		case BaseCommand::START:
			if (taskType == TaskType::CPP)
			{
				startCPP(process, taskName);
			}
			else
			{
				assert(taskType == TaskType::SHELL);
				startSHELL(process, taskName);
			}
			break;

		case BaseCommand::PAUSE:
			pause(taskName);
			break;

		case BaseCommand::RESUME:
			resume(taskName);
			break;

		case BaseCommand::STOP:
			stop(taskName);
			break;

		case BaseCommand::QUIT:
			killAllTasks();
			break;

		case BaseCommand::STATUS:
			if (taskName == "")
				status();
			else
				varToReturn = status(taskName);
			break;

		case BaseCommand::HELP:
			throw helpInfo();
			break;	

		default:
			throw helpInfo();			
			break; // Not necessary break statement.	
	}

	return varToReturn;
}






std::string TaskManager::startUsage() const
{
	return "Start:\t\tUsage is 'start <task_type> <task_name> <shell process or functionName>'. The <task_type> is either 'CPP' or 'SHELL'.\n\n";
}

std::string TaskManager::pauseUsage() const
{
	return "Pause:\t\tUsage is 'pause <task_name>'.\n\n";
}

std::string TaskManager::statusUsage() const
{
	return "Status:\t\tUsage is 'status <task_name>'. The <task_name> is here optional. In absence of task_name, the status of all classes will be listed\n\n";
}


std::string TaskManager::stopUsage() const
{
	return "Stop:\t\tUsage is 'stop <task_name>'.\n\n";
}

std::string TaskManager::quitUsage() const
{
	return "Quit:\t\tUsage is just 'quit', with nothing afterward.\n\n"; // This command quits the application and kill all tasks in doing so. When receiving a SIGINT, the application also kill all processes before quiting. Hence, doing 'command + c' or 'control + c' should be equivalent to typing 'quit'
}

std::string TaskManager::resumeUsage() const
{
	return "Resume:\t\tUsage is 'resume <task_name>'.\n\n";
}

std::string TaskManager::helpInfo() const
{
	return  std::string("\n\n") + std::string("TaskManager is a little tool to manage tasks that are either hard wired in C++ (see the files predefinedTasks.h, predefinedTasks.cpp) or that are expressed directly in Shell script. When starting a task (with C++ hard wired task or a shell task), you need to name it. Then, you can inquire the status of the task and you can chose to pause the task, resume it or stop it at wish.\n\n") + startUsage() + pauseUsage() + stopUsage() + quitUsage() + resumeUsage() + "Note that TaskManager is also a library that can be used from your C++ code and it then can read commands in a format that is more computer friendly than a string. I am however too tired to explain that now! Sweet dreams!\n\n";
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
