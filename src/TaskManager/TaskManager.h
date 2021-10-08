#ifndef TaskManager_H
#define TaskManager_H

#include "TypeDefinitions.h"
#include "Task.h"
#include <vector>
#include <unordered_map>

class TaskManager
{
public:

	enum BaseCommand {START, PAUSE, RESUME, STOP, STATUS, QUIT, HELP};
	enum TaskType {CPP, SHELL, UNKNOWN};
	
	TaskManager();
	~TaskManager();

	int submit(const std::string& input);

	int submit(
		const BaseCommand baseCommand,  // start, resume, pause, stop, quit
		const TaskType taskType,  	   	// CPP or SHELL
		const std::string& taskName,    // Casual name to refer to this task
		const std::string& process     	// Name of CPP function or full Shell process
	);

	void printLogo() const;
	void printVersion() const;
	void printHelp() const;
	bool hasQuitted() const;

private:	
	/*
		Using polymorphism here in vector tasks with TaskSHELL and TaskCPP. Tasks will stack up here. We keep all the tasks so that we can tell apart unknown tasks from those that have stopped (killed) or were completed
	*/


	std::vector<Task*> tasks; 
	std::unordered_map<std::string, taskID_t> NamesIDsmap;
	bool _hasquitted;
	std::string _version = "version 0.1.0";


	/*
		Class actions
	*/


	void startSHELL(const std::string& process, const std::string& taskName);
	void startCPP(const std::string& functionName, const std::string& taskName);
	void pause(const taskID_t taskID);
	void pause(const std::string& taskName);
	void resume(const taskID_t taskID);
	void resume(const std::string& taskName);
	void stop(const taskID_t taskID);
	void stop(const std::string& taskName);
	void status();
	int status(const taskID_t taskID);
	int status(const std::string& taskName);

	/*
		Kill all tasks
	*/
	void killAllTasks();

	/*
		Functions that return usage information
	*/

	std::string helpInfo() const;
	std::string startUsage() const;
	std::string pauseUsage() const;
	std::string stopUsage() const;
	std::string quitUsage() const;
	std::string resumeUsage() const;
	std::string statusUsage() const;

	/*
		Functions to ensure we keep a good track of processes
	*/

	void checkTaskID(const taskID_t& taskID) const;
	taskID_t findTaskIDFromName(const std::string& taskName) const;
	void addTaskToMap(const std::string& taskName);

};


#endif /* TaskManager_H */
