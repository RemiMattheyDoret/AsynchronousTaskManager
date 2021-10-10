#ifndef PREDEFINEDFUNCTIONS_H
#define PREDEFINEDFUNCTIONS_H

#include "CppProcessController.h"

class PredefinedCppTasks
{
public:
	/*
		Example of tasks to perform
	*/
	
	static void doThis(CppProcessController&& controller);
	static void doThat(CppProcessController&& controller);
	static void i_am_a_ghost(CppProcessController&& controller);
	static void isSoftwareDeveloperAGoodJob(CppProcessController&& controller);

	static void duration_5s(CppProcessController&& controller);
	static void duration_50s(CppProcessController&& controller);
	static void duration_500s(CppProcessController&& controller);


	/*
		This function is called by TaskManager
	*/

	static const function_t get_fct_from_fctName(const std::string& functionName);

private:
	// Helper functions for those tasks
	static unsigned long long factorial(int n);
	static void duration_xs(CppProcessController&& controller, unsigned x);
};

#endif /* PREDEFINEDFUNCTIONS_H */