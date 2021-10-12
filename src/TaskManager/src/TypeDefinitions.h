#include <functional>

// Type of PID (Process IDentifier in the system)
using PID_t = int;

// Type of taskID (task IDentifier in the AsynchronousTaskManager library)
using taskID_t = long int; 

/*
	All tasks have a taskID.
	Predefined tasks (CPP tasks) only have a taskID and no PID.
	Shell tasks are run with the `system` command and therefore have a PID.
*/

// Types of functions that are hard wired (for CPPTask)
class CppProcessController; // forward declaration
using function_t = std::function<void(CppProcessController&&, const std::string&)>;
