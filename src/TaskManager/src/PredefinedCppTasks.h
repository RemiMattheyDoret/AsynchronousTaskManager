#ifndef PREDEFINEDFUNCTIONS_H
#define PREDEFINEDFUNCTIONS_H

#include "CppProcessController.h"

class PredefinedCppTasks
{
public:
	/*
		Example of tasks to perform

		  ! WARNING !
		When adding a function, you must make sure that the method 'get_fct_from_fctName' will be able to match its name to this function to return it otherrwise the functin will not be avaialbale to the user.
		I could also store functions and their names in an array of pairs (or in a map) instead to avoid this complication but we would still need to update this array or map.
		Sorry, C++ dooe snot allow reflection. A better solution miight be achievablee with some fancy macros.
	*/
	
	static void factorials(CppProcessController&& controller, const std::string& filePath);
	static void doThat(CppProcessController&& controller, const std::string& filePath);
	static void isSoftwareDeveloperAGoodJob(CppProcessController&& controller, const std::string& filePath);
	static void duration_5s(CppProcessController&& controller, const std::string& filePath);
	static void duration_50s(CppProcessController&& controller, const std::string& filePath);
	static void duration_500s(CppProcessController&& controller, const std::string& filePath);
	static void pikachu(CppProcessController&& controller, const std::string& filePath);


	/*
		'get_fct_from_fctName' is called by TaskManager and the function is then given to TaskCpp at instantiation.
	*/

	static const function_t get_fct_from_fctName(const std::string& functionName);

private:
	// Helper functions for those tasks
	static unsigned long long factorial(int n);
	static void duration_xs(CppProcessController&& controller, unsigned x, const std::string& filePath);
};

#endif /* PREDEFINEDFUNCTIONS_H */
