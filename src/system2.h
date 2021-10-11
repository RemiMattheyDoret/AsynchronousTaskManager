#ifndef SYSTEM2_H
#define SYSTEM2_H


/*
    I stole this piece of code from https://stackoverflow.com/questions/22802902/how-to-get-pid-of-process-executed-with-system-command-in-c and modified it a little bit to fit my needs

    system2 does not pauses like system1. It is therefore easier to get the PID from the submitted process.

    system2 runs the command and return the PID of this command

*/

#include "TypeDefinitions.h"

PID_t system2(const char * command);


#endif /* SYSTEM2_H */