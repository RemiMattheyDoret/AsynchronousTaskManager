
## TaskManager

TaskManager is a little C++ software package whose purpopse is to simplify the management of asynchronous tasks. There are two types of tasks that can be submitted to a TaskManager object; a predefined (hard-wired) function in C++ or any SHELL command line.

After starting them, tasks can then be paused, resume or stopped at will. TaskManager also return the status of those tasks.


## Installation

**Requirements**

Compilation will require C++ (C++17 or higher).

To compile the tests, you will also need gtest (google test).


**How to install**

Clone the *TaskManager* repository. 

`git clone https://github.com/RemiMattheyDoret/TaskManager`

Change directory to the TaskManager directory.

`cd TaskManager`

Compile the main executable

`make`

The executable is called `TaskManager` should be in `TaskManager/bin/`


In order to compile the tests, you will need googltest. If googltests are not installed on your machine yet, you can do 

```
git clone https://github.com/google/googletest
cd googletest
mkdir build
cd build
cmake ..
make
make install
```
To compile the tests, then do 

`make test`

The executable is `test` present at `TaskManager/bin/`. Making tests will also create a static library called `TaskManager.a` in `src/TaskManager/lib/`. Feel free to `install` it if you wish.


## Code organization

<ins>**TaskManager**</ins>

The most important class of the library is *TaskManager*. *TaskManager* reads input from the user through the *submit()* function. The user can either submit the input through a string (as is done when reading directly from the command line) or through and more organized manner (as is done when including the package directly in your C++ code). *TaskManager* parses the input, and instantiate the right *Task* object to initiate the task (aka. the process). *TaskManager* also keep pointers to those tasks in memory along with the task identifier given from the user.


<ins>**Task**, **TaskCpp**, and **TaskShell**</ins>

A user can submit two types of tasks to *TaskManager*; 1) tasks that are predefined in C++ and 2) tasks that aree written in Shell script. For the first and second type of tasks, *TaskManager* creates an instance of class *TaskCpp* and *TaskShell*, respectively. *TaskCpp* and *TaskShell*, both inherit from the abstract class *Task*.

As soon as a *Task* objects is instantiated, the process of interest starts running. The *Task* objects are also responsible for pausing, resuming and stopping the process upon demand from the *TaskManager* (and therefore\e ultimately from the user).


<ins>**PredefinedCppTasks**</ins>

Tasks that are predefined in C++ are stored in the class *PredefinedCppTasks*. The *TaskManager* calls a static method of *PredefinedCppTasks*, give it the name of the function specified by the user in argument and receives a copy of the function to run. This is then used when instantiating the *TaskCpp*


<ins>**CppProcessController**</ins>

While *TaskShell* objects are able to pause, resume, stop and check status of the process on its own, the *TaskCpp* object needs some help. This help comes from a *CppProcessController* object type. A *TaskShell* starts the process of interest in a seperate thread using a *std::thread* object. A *CppProcessController* is given to the *std::thread* object and is responsible for controlling the process flow (e.g. pause the process when it needs to be paused).

## Usage

The *TaskManager* library is meant to either be used through the command line or embedded within you C++ code. I will here only talk about the case when *TaskManager* is used from the command line. In such case, the library *TaskManager* is here wrapped in a int main() function that will submit tasks from user input through the command line. Note that the parsing of the command line is made by the *TaskManager* itself. First when calling, the executable you can print help or the version with the following:

`./TaskManager --help`

and

`./TaskManager --version`

If you just run the executable without arguments (`./TaskManager`), then you will be prompted to input commands. There are 5 possible basic commands; `start`, `pause`, `resume`, `stop`, `quit`, and `help`. Here is a description of their usage

<ins>**start:**</ins>

Starts a new process

Usage is `start <task_type> <task_name> <process_info>`. The <task_type> is either 'CPP' (or 'cpp') or 'SHELL' (or 'shell'). The <task_name> is an identifier for the process that you can later use to control (pause, resume or stop) the process. The <task_name> is made of any string of one or more characters excluding spaces and tabs). 

When the <task_type> is 'CPP' (or 'cpp'), then you need to provide the *function_name* as <process_info>. The currently predefined function names are:
	- factorials
	- doThat
	- isSoftwareDeveloperAGoodJob
	- duration_5s
	- duration_50s
	- duration_500s
	- pikachu

You can as well specify an optional *filePath* where the output of the task will be printed. Here is an example

```start cpp mySuperTask pikachu /Users/remi/test/PikaPika.txt```

It is adviced to use an absolute path.

When the <task_type> is 'SHELL', then you need to provide the <shell_process> as last argument. The <shell_process> is any process written in Shell. Here is an example

```start shell I_prefer_Alice cd /Users/remi/test; for f in *.txt; do sed 's/Barbara/Alice/g' $f > tmp && mv tmp $f ;done```

Note that TaskManager only reads one line from the command line. So, if you problem is too complexe, please write it on a file and source the file.

<ins>**status:**</ins>

Returns the status of a process that has been started earlier

Usage is `status <task_name>`. There are four possible statuses; running, paused, stopped or completed. Processes that are stopped or completed cannot have a change of status. It is also possible to leave the <task_name> empty (just `status`) and TaskManager will print all task names (in no particular order) along with their statuses.

<ins>**progress:**</ins>

Returns the progress of a process that has been started earlier. This only works for CPP tasks

Usage is `progress <task_name>`. Note that the 'progress' of a task is reported by the running functin itself, whille the status is controlled by the ProcessController. It is therefore not impossible to observe slight mismatches. A function may also decide not to report progress (because that can be a difficult thing to report). In such case, it will print out 'progress undefined'.

<ins>**pause:**</ins>

Pauses a process that has been started earlier

Usage is `pause <task_name>`, where <task_name> is the name of a task started earlier. Only running tasks can be paused.

<ins>**resume:**</ins>

Resumes a process that has been paused earlier

Usage is `resume <task_name>`, where <task_name> is the name of a task started earlier. Only paused tasks can be resumed.

<ins>**stop:**</ins>

Stops a process that is either running or paused (but not completed or already stopped).

Usage is `resume <task_name>`, where <task_name> is the name of a task started earlier.

<ins>**help:**</ins>

Prints usage information

usage is `help`.
