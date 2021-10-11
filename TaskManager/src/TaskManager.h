#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "TypeDefinitions.h"
#include "Task.h"
#include "TaskCpp.h"
#include "TaskShell.h"
#include <vector>
#include <string>
#include <unordered_map>

class TaskManager
{
public:

	enum BaseCommand {START, PAUSE, RESUME, STOP, STATUS, QUIT, HELP};
	enum TaskType {CPP, SHELL, UNKNOWN};
	
	TaskManager();
	~TaskManager();

	/*
		int 'submit(const std::string& input);' is actually parsing the input and resubmitting it to the other 'submit' method. This causes unnecessary case switch statements but it felt safer that wether the user uses one or the other 'submit' command, then in all cases, it will go through the same submission process after eventual parsing.
	*/

	int submit(const std::string& input);

	void printLogo() const;
	void printVersion() const;
	void printHelp() const;
	bool hasQuitted() const;



	void startShell(const std::string& taskName, const std::string& process);
	void startCpp(const std::string& taskName, const std::string& functionName, const std::string& filePath);
	void pause(const taskID_t taskID);
	void pause(const std::string& taskName);
	void resume(const taskID_t taskID);
	void resume(const std::string& taskName);
	void stop(const taskID_t taskID);
	void stop(const std::string& taskName);
	std::vector<std::pair<std::string, Task::TaskStatus>> status();
	int status(const taskID_t taskID);
	int status(const std::string& taskName);
	std::vector<std::pair<std::string, Task::TaskStatus>> listTasks(Task::TaskStatus status = Task::TaskStatus::defaultValue);
	void quit();

private:
	struct Command;	
	/*
		Using polymorphism here in vector tasks with TaskShell and TaskCpp. Tasks will stack up here. We keep all the tasks so that we can tell apart unknown tasks from those that have stopped (killed) or were completed
	*/


	std::vector<Task*> tasks; 
	std::unordered_map<std::string, taskID_t> NamesIDsmap;
	bool _hasquitted;
	std::string _version = "version 1.0.1";


	

	/*
		Kill all tasks
	*/
	void killAllTasks();

	/*
		Functions that return usage information
	*/

	std::string incorrectFormatMessage() const;
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


/*
	Private nested class 'Command'
*/

struct Command
{
	enum BaseCommand {start, pause, resume, stop, status, quit, help};
	enum TaskType {CPP, SHELL, UNKNOWN};
	
	BaseCommand _baseCommand;
	TaskType _taskType;
	std::string _taskName;
	std::string _process;

	//taskID_t taskID;
};


#endif /* TASKMANAGER_H */
