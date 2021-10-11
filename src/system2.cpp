
/*
    I stole this piece of code from https://stackoverflow.com/questions/22802902/how-to-get-pid-of-process-executed-with-system-command-in-c and modified it a little bit to fit my needs

    system2 does not pauses like system1. It is therefore easier to get the PID from the submitted process.

    system2 runs the command and return the PID of this command

*/

#include "TypeDefinitions.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "system2.h"



PID_t system2(const char * command)
{
    //std::cout << command << "\n";

    int p_stdin[2];
    int p_stdout[2];
    PID_t pid;

    if (pipe(p_stdin) == -1)
        return -1;

    if (pipe(p_stdout) == -1) {
        close(p_stdin[0]);
        close(p_stdin[1]);
        return -1;
    }

    pid = fork();

    if (pid < 0) {
        close(p_stdin[0]);
        close(p_stdin[1]);
        close(p_stdout[0]);
        close(p_stdout[1]);
        return pid;
    } else if (pid == 0) {
        close(p_stdin[1]);
        dup2(p_stdin[0], 0);
        close(p_stdout[0]);
        dup2(p_stdout[1], 1);
        dup2(::open("/dev/null", O_RDONLY), 2);
        /// Close all other descriptors for the safety sake.
        for (int i = 3; i < 4096; ++i)
            ::close(i);

        setsid();
        execl("/bin/sh", "sh", "-c", command, NULL);
        _exit(1);
    }

    close(p_stdin[0]);
    close(p_stdout[1]);

    //std::cout << "pid = " << pid << std::endl;

    return pid;
}
