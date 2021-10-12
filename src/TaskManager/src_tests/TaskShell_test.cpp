#include <cstdio>
#include <filesystem>

int number_of_lines(const std::string& path)
{
	int number_of_lines = 0;
    std::string line;
    std::ifstream myfile;
    myfile.open(path);

    while (std::getline(myfile, line))
        ++number_of_lines;
    return number_of_lines;
}




TEST(TaskShellTest, testBadProcessFormulation_A)
{	
	/*
		Non-sense process
	*/
	std::string process = "Isaac Asimov";
	TaskShell task(process);

	// Wait to make sure the process can start and crash and then assert it is completed
	std::this_thread::sleep_for(std::chrono::seconds(1));
	EXPECT_EQ(task.status(), Task::TaskStatus::completed);
}

TEST(TaskShellTest, testBadProcessFormulation_B)
{	
	/*
		space
	*/
	std::string process = " ";
	TaskShell task(process);

	// Wait to make sure the process can start and crash and then assert it is completed
	std::this_thread::sleep_for(std::chrono::seconds(1));
	EXPECT_EQ(task.status(), Task::TaskStatus::completed);
}


TEST(TaskShellTest, testBadProcessFormulation_C)
{	
	/*
		Empty string
	*/
	std::string process = "";
	TaskShell task(process);

	// Wait to make sure the process can start and crash and then assert it is completed
	std::this_thread::sleep_for(std::chrono::seconds(1));
	EXPECT_EQ(task.status(), Task::TaskStatus::completed);
}

TEST(TaskShellTest, testBadProcessFormulation_D)
{	
	/*
		Sring where CLI expects an closing symbol
	*/
	std::string process = "' % dd kfau $$%$! `ç%d ";
	TaskShell task(process);

	// Wait to make sure the process can start and crash and then assert it is completed
	std::this_thread::sleep_for(std::chrono::seconds(1));
	EXPECT_EQ(task.status(), Task::TaskStatus::completed);
}	


TEST(TaskShellTest, testStatus_A)
{
	/*
		It is not so easy to test a process running on the shell. So, I am using large time intervals to test when the process is actually running or not.
		Test pausing, resuming and completion
	*/

	std::string path = std::string(std::filesystem::temp_directory_path()) + std::string("testStatus_A.txt");
	std::string process = std::string("cat /dev/null > ") + path + std::string(";sleep 3s; for i in {1..10}; do echo ${i} >> ") + path + std::string("; done; sleep 3s; for i in {11..20}; do echo ${i} >> ") + path + std::string("; done");

	// Run task and check it is running
	TaskShell task(process);
	EXPECT_EQ(task.status(), Task::TaskStatus::running);

	// Sleep and make sure we got 10 lines and it is still running
	std::this_thread::sleep_for(std::chrono::seconds(4));
	auto nbLines = number_of_lines(path);

	EXPECT_EQ(nbLines, 10);
	EXPECT_EQ(task.status(), Task::TaskStatus::running);

	// Pause process and wait to make sure it was indeed paused
	task.pause();
	EXPECT_EQ(task.status(), Task::TaskStatus::paused);
	std::this_thread::sleep_for(std::chrono::seconds(4));
	EXPECT_EQ(nbLines, number_of_lines(path));

	// ensure it cannot pause again
	bool failedToPause = false;
	try {
		task.pause();
	} catch (...)
	{
		failedToPause = true;
	}
	ASSERT_TRUE(failedToPause);


	// Resume and make sure it is running.
	task.resume();
	EXPECT_EQ(task.status(), Task::TaskStatus::running);

	// Sleep and make sure the program ended and that we observe the right number of lines
	std::this_thread::sleep_for(std::chrono::seconds(4));
	EXPECT_EQ(task.status(), Task::TaskStatus::completed);
	nbLines = number_of_lines(path);
	EXPECT_EQ(nbLines, 20);	


	std::remove(path.c_str());
}
		

TEST(TaskShellTest, testStatus_B)
{
	/*
		Test stopping a process
	*/

	std::string path = std::string(std::filesystem::temp_directory_path()) + std::string("testStatus_B.txt");
	std::string process = std::string("cat /dev/null > ") + path + std::string(";sleep 3s; for i in {1..10}; do echo ${i} >> ") + path + std::string("; done; sleep 3s; for i in {11..20}; do echo ${i} >> ") + path + std::string("; done");

	
	// Run task and check it is running
	TaskShell task(process);
	EXPECT_EQ(task.status(), Task::TaskStatus::running);

	// Wait until it sleeps, then stop, test its status and check number of lines
	std::this_thread::sleep_for(std::chrono::seconds(4));
	task.stop();
	EXPECT_EQ(task.status(), Task::TaskStatus::stopped);
	EXPECT_EQ(10, number_of_lines(path));

	// Ensure it cannot be restarted
	bool failedToResume = false;
	try {
		task.resume();
	} catch (...)
	{
		failedToResume = true;
	}
	ASSERT_TRUE(failedToResume);
	std::remove(path.c_str());
}	




