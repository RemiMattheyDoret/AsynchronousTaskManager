
### Compiler and Flags
CC := g++
CFLAGS := -std=gnu++11 -O0 -Wall -fmax-errors=5

### target and objects
target := callAsynchronousTaskManager
objs := src/main.o src/AsynchronousTaskManager/AsynchronousTaskManager.o src/AsynchronousTaskManager/Task.o src/AsynchronousTaskManager/Command.o src/AsynchronousTaskManager/TaskManager.o src/AsynchronousTaskManager/TaskCPP.o src/AsynchronousTaskManager/TaskSHELL.o src/AsynchronousTaskManager/PredefinedTasks.o src/AsynchronousTaskManager/system2.o src/AsynchronousTaskManager/ProcessController.o src/AsynchronousTaskManager/typeDefinitions.o

### Dependencies
# gcc -c main.c --MMD -MF main.d
# cat main.d   -> main.o: main.c something.h
# deps := $(patsubst %.o,%.d,$(objs)) -include $(deps) DEPFLAGS=-MMD -MF $(@:.o=d)


# $@: replace name of target
# $<: replace name of first prerequisite
# $^: replace names of all prerequisite


all: $(target)

callAsynchronousTaskManager: $(objs)
	$(CC) $(CFLAGS) $^ -o $@ 

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean: 
	rm *.o $(target)
