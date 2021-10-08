#ifndef TaskManager_H
#define TaskManager_H

#include "TypeDefinitions.h"
#include "Task.h"
#include <vector>
#include <unordered_map>

class TaskManager
{
public:
	void startSHELL(std::string& process, std::string& taskName);
	void startCPP(std::string& functionName, std::string& taskName);
	void pause(taskID_t taskID);
	void pause(std::string& taskName);
	void resume(taskID_t taskID);
	void resume(std::string& taskName);
	void stop(taskID_t taskID);
	void stop(std::string& taskName);
	void status(taskID_t taskID);
	void status(std::string& taskName);
	~TaskManager();

private:	
	/*
		Using polymorphism here in vector tasks with TaskSHELL and TaskCPP. Tasks will stack up here. We keep all the tasks so that we can tell apart unknown tasks from those that have stopped (killed) or were completed
	*/
	std::vector<Task*> tasks; 
	std::unordered_map<std::string, taskID_t> NamesIDsmap;

	void checkTaskID(taskID_t& taskID);
	taskID_t findTaskIDFromName(std::string& taskName);
	void addTaskToMap(std::string& taskName);

};


#endif /* TaskManager_H */
