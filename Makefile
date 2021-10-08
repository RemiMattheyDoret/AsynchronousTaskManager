
### Compiler and Flags
CC := g++
CFLAGS := -std=gnu++11 -O0 -Wall -fmax-errors=5

### target and objects
target := callAsynchronousTaskManager
objs := src/main.o src/AsynchronousTaskManager/AsynchronousTaskManager.o src/AsynchronousTaskManager/Task.o src/AsynchronousTaskManager/TaskManager.o src/AsynchronousTaskManager/TaskCPP.o src/AsynchronousTaskManager/TaskSHELL.o src/AsynchronousTaskManager/PredefinedTasks.o src/AsynchronousTaskManager/system2.o src/AsynchronousTaskManager/ProcessController.o

### Dependencies
# gcc -c main.c --MMD -MF main.d
# cat main.d   -> main.o: main.c something.h
# deps := $(patsubst %.o,%.d,$(objs)) -include $(deps) DEPFLAGS=-MMD -MF $(@:.o=d)


# $@: replace name of target
# $<: replace name of first prerequisite
# $^: replace names of all prerequisite


#all: $(target)

$(target): $(objs)
	$(CC) $(CFLAGS) $^ -o bin/$@ 

#src/main.o: src/main.cpp:
	#$(CC) $(CFLAGS) -c main.cpp

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test: 
	$(CC) $(CFLAGS) src/main_tests.cpp -o bin/tests

clean: 
	rm src/*.o src/AsynchronousTaskManager/*.o $(target)
