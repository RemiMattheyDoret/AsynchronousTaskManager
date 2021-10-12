#ifndef SYSTEM2_H
#define SYSTEM2_H


/*
    system2 runs a shell command in the background and return the PID.

*/

#include "TypeDefinitions.h"

PID_t system2(const char * command);


#endif /* SYSTEM2_H */