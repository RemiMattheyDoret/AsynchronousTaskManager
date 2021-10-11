### Compiler and Flags
CC := clang++
CFLAGS := -std=c++17 -O2 -Wall -pthread -I/usr/local/bin/
CFLAGS_test := -std=c++17 -O2 -Wall -lgtest -pthread -I/usr/local/bin/

### target and objects
target := TaskManager
mainObj := src/main.o
libObjs :=  src/TaskManager/src/TaskManager.o src/TaskManager/src/Task.o src/TaskManager/src/TaskCpp.o src/TaskManager/src/TaskShell.o src/TaskManager/src/PredefinedCppTasks.o src/TaskManager/src/CppProcessController.o src/TaskManager/src/system2.o

### Building library
lib := src/TaskManager/lib/TaskManager.a

### For install, make sure to set PREFIX if therre is no default
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif


# $@: replace name of target
# $<: replace name of first prerequisite
# $^: replace names of all prerequisite


#all: $(target)

$(target): $(mainObj) $(libObjs)
	$(CC) $(CFLAGS) $^ -o bin/$@ 


%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test: $(lib)
	$(CC) $(CFLAGS_test) src/main_tests.cpp $(lib) -o bin/tests

install: $(lib)
	install  $(lib) $(PREFIX)/lib/
	install  src/TaskManager/src/TaskManager.h $(PREFIX)/include/

$(lib): $(libObjs)
	ar rsv $(lib) $(libObjs)



clean: 
	rm src/*.o src/TaskManager/src/*.o bin/* $(lib)
