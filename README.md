
## TaskManager

TaskManager is a little C++ software package whose purpopse is to simplify the management of asynchronous tasks. There are two types of tasks that can be submitted to a TaskManager object; the name of a predefined function in C++ and a SHELL command line.

After starting them, tasks can then be paused, resume or stopped at will. TaskManager also return the status of those tasks.


## My Motivation

I built it over a few days for a job application.


## Tech/Framework used

Plain C++ standard of 2011 minimum and Googltest for unit testing. A little makefile to compile.

## Code Style

Coded with rush at night time after work. That's the style!

## Code organization

**TaskManager**

The most important class of the library is *TaskManager*. *TaskManager* reads input from the user through the *submit()* function. The user can either submit the input through a string (as is done when reading directly from the command line) or through and more organized manner (as is done when including the package directly in your C++ code). *TaskManager* parses the input, and instantiate the right *Task* object to initiate the task (aka. the process). *TaskManager* also keep pointers to those tasks in memory along with the task identifier given from the user.


**Command**

*Command* is a privated nested class of *TaskManager*. *TaskManager* uses a *Command* object to simplify the representation of the user request. *Command* is of POD (Plain Old Data) type.


**Task**, **TaskCpp**, and **TaskShell**

A user can submit two types of tasks to *TaskManager*; 1) tasks that are predefined in C++ and 2) tasks that aree written in Shell script. For the first and second type of tasks, *TaskManager* creates an instance of class *TaskCpp* and *TaskShell*, respectively. *TaskCpp* and *TaskShell*, both inherit from the abstract class *Task*.

As soon as a *Task* objects is instantiated, the process of interest starts running. The *Task* objects are also responsible for pausing, resuming and stopping the process upon demand from the *TaskManager* (and therefore\e ultimately from the user).


**PredefinedCppTask**

Tasks that are predefined in C++ are stored in the class *PredefinedCppTask*. The *TaskManager* calls a static method of *PredefinedCppTask*, give it the name of the function specified by the userr in argument and receives a copy of the function to run. This is then used when instantiating the *TaskCpp*


**CppProcessController**

While *TaskShell* objects are able to start, pause, resume, stop and check status of the process on its own, thee *TaskCpp* object needs some help. This help comes from a *CppProcessController* object type. A *TaskShell* submit the process of interest in a seperate thread using a *std::thread* object. A *CppProcessController* is given to the *std::thread* object and is responsible for controlling the process flow (e.g. pause the process when it needs to be paused).

## Usage

The *TaskManager* library can take task submission either from a set of arguments (handy when calling the *TaskManager* directly from a C++ code) or from a string (handy when submitting tasks from the command line). Below, I am describing the second usage.

The library is here wrapped in a int main() function that will submit tasks from user input through the command line. First when calling, the executable you can print help or the version with the following:

`./TaskManager --help`

and

`./TaskManager --version`

If you just run the executable without arguments (`./TaskManager`), then you will be prompted to input commands. There are 5 possible basic commands; `start`, `pause`, `resume`, `stop`, `quit`, and `help`. Here is a description of their usage

**Start:**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Starts a new process
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Usage is 'start <task_type> <task_name> <shell_process or function_name>'. The <task_type> is either 'CPP' or 'SHELL'. The <task_name> is an identifier for the process.made The <task_name> is made of any string of one or more characters excluding spaces and tabs). When the <task_type> is 'CPP', then you need to provide the <function_name> as last argument. the <function_name> is a hard wired function saved in the class *CppProcessController*. When the <task_type> is 'SHELL', then you need to provide the <shell_process> as last argument. The <shell_process> is any process written in Shell.

**status**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Returns the status of a process that has been started earlier
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;There are four possible statuses; running, paused, stopped or completed. Processes that are stopped or completed cannot have a change of status.

**pause**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Pauses a process that has been started earlier
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Usage is 'pause <task_name>', where <task_name> is the name of a task started earlier. Only running tasks can be paused.

**resume**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Resumes a process that has been paused earlier
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Usage is 'resume <task_name>', where <task_name> is the name of a task started earlier. Only paused tasks can be resumed.

**stop**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Stops a process that is either running or paused (but not completed or already stopped).
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Usage is 'resume <task_name>', where <task_name> is the name of a task started earlier.



## Screenshot
