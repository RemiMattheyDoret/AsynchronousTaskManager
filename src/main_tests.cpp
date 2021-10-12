#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>

//#include "TaskManager/src/typeDefinitions.h"
#include "TaskManager/src/Task.h"
#include "TaskManager/src/TaskShell.h"
#include "TaskManager/src/TaskCpp.h"
#include "TaskManager/src/CppProcessController.h"
#include "TaskManager/src/TaskManager.h"
#include "TaskManager/src/PredefinedCppTasks.h"


#include "TaskManager/src_tests/TaskManager_test.cpp"
#include "TaskManager/src_tests/TaskShell_test.cpp"
#include "TaskManager/src_tests/system2_test.cpp"
#include "TaskManager/src_tests/TaskCpp_test.cpp"
#include "TaskManager/src_tests/CppProcessController_test.cpp"


int main(int argc, char** argv)
{
	std::cout << "\n\nWARNING!\nThe tests depends upon the relative processing times of asynchronous tasksto make sure those tasks are paused and resume as expected. The tests take large safety margin (hence why they are so slow) but if your machine is very busy and a asynchronous task might be set aside for over 2 seconds, then it is possible the test would fail in absence of any bug. I have tried to cause the tests to fail by running heavy processes in parallel and the tests have never failed but we never know. So please, if the tests fail, calm your machine down andd retry!\n\n\n" << std::flush;

	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
