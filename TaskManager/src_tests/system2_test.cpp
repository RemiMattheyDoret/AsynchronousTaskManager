#include <cstdio>
#include <filesystem>
#include "signal.h"


bool is_pid_running(int pid)  
{

	/*
		I just copy-pasted the code from https://stackoverflow.com/questions/12601759/determine-if-a-process-exists-from-its-process-id/20240710
	*/

    while(waitpid(-1, 0, WNOHANG) > 0) {
        // Wait for defunct....
    }

    if (0 == kill(pid, 0))
        return 1; // Process exists

    return 0;
}



TEST(TaskShellTest, TestSystem2)
{
	// Start process and save PID
	int pid = system2("sleep 3s");

	// Ensure PID is existing
	ASSERT_TRUE(is_pid_running(pid));

	// Wait and ensure PID does not exist anymore
	std::this_thread::sleep_for(std::chrono::seconds(4));
	ASSERT_FALSE(is_pid_running(pid));
}

