#include "TaskManager/src/TaskManager.h"
#include "TaskManager/src/Task.h"
#include <iostream>
#include <cstring>


/*
	This main function goes in a while loop. At each iteartion, it listens to user input and submit it to a 'TaskManager' called 'tm'
*/


int main(int argc, char *argv[])
{
	/*
		Create instance of TaskManager.
	*/

	TaskManager tm; 

	/*
		Address arguments to executable
	*/

	if (argc > 1)
	{
		if (argc > 2)
		{
			std::cout << "The executable accepts one argument at most (either --version or --help).\n";
			std::exit(1);
		}
		if (strcmp(argv[1], "--version") == 0)
		{
			tm.printVersion();
		} else if (strcmp(argv[1], "--help") == 0)
		{
			tm.printHelp();
		} else
		{
			std::cout << "Unknown argument " << argv[1] << " received. The executable only accepts --version or --help. If you just call ./TaskManager without argument, then you will be asked to prompt more information.\n";
			std::exit(1);
		}
		return 0;
	}



	/*
		Print TaskManager logo
	*/

	tm.printLogo();


	/*
		Loop through each user input
	*/

	while (true)
	{
		try
		{
			/*
				Read command line from user
			*/
			std::string input;
			std::cout << "I'm listening, honey: ";
			getline(std::cin, input);

			/*
				Submit command line to atm
				If you asked for _status then, the return valule is the status which you can compare the #defined PAUSED RUNNING STOPPED COMPLETED.
				For this example, I just let atm prints out the _status in a nice format.
			*/

			auto value = tm.submit(input);


			switch (value)
			{
				case Task::TaskStatus::paused:
					std::cout << "\tpaused\n";
					break;
				case Task::TaskStatus::running:
					std::cout << "\trunning\n";
					break;
				case Task::TaskStatus::stopped:
					std::cout << "\tstopped\n";
					break;
				case Task::TaskStatus::completed:
					std::cout << "\tcompleted\n";
					break;
			}

			/*
				Note that there are two ways to submit something to the TaskManager. Here is an example

					submit("start SHELL myShellTask sleep 10s")

				is equivalent to

					submit(
						TaskManager::BaseCommand::START,
						TaskManager::TaskType::SHELL,
						"myShellTask",
						"sleep 10s"
					)
			*/

		}

		/*
			Catch exceptions
		*/
	    catch (const std::string& e)
	    {
	        std::cout << "\t" << e << std::endl;
	    }
	    catch (...)
	    {
	        std::cout << "Received some unexpected exception! Sounds like a bug! I'm exiting. Sorry\n";
	        std::exit(1);
	    }


	    /*
			TaskManager kills all the tasks upon reception of the 'quit' keyword. When atm has quitted, main will also quit here.
		*/
		if (tm.hasQuitted())
		{
			std::cout << "\n\t\t----- Ciao! -----\n\n";
			return 0;
		}
	}
}
