



TEST(TaskCpp, testStatus_A)
{
	std::string fct_name = "duration_5s";
	auto fct = PredefinedCppTasks::get_fct_from_fctName(fct_name);

	/*
		Test pausing, resuming and completion
	*/

	// initialize and make sure it runs
	TaskCpp task(fct);
	EXPECT_EQ(task.status(), Task::TaskStatus::running);

	// Pause and ensure it has paused and then wait
	task.pause();
	EXPECT_EQ(task.status(), Task::TaskStatus::paused);
	std::this_thread::sleep_for(std::chrono::seconds(6));
	EXPECT_EQ(task.status(), Task::TaskStatus::paused);

	// resume and pause again
	task.resume();
	EXPECT_EQ(task.status(), Task::TaskStatus::running);
	task.pause();
	EXPECT_EQ(task.status(), Task::TaskStatus::paused);

	// resume again
	task.resume();
	EXPECT_EQ(task.status(), Task::TaskStatus::running);

	// Ensure you cannot resume a process that is already running
	bool failedToResume = false;
	try{
		task.resume();
	}catch(...)
	{
		failedToResume = true;
	}
	ASSERT_TRUE(failedToResume);

	// Wait for completion
	std::this_thread::sleep_for(std::chrono::seconds(6));
	EXPECT_EQ(task.status(), Task::TaskStatus::completed);

}

TEST(TaskCpp, testStatus_B)
{
	std::string fct_name = "duration_5s";
	auto fct = PredefinedCppTasks::get_fct_from_fctName(fct_name);

	/*
		Test stopping
	*/

	// initialize and make sure it runs
	TaskCpp task(fct);
	EXPECT_EQ(task.status(), Task::TaskStatus::running);


	// stops
	task.stop();
	EXPECT_EQ(task.status(), Task::TaskStatus::stopped);

	// ensure you cannot change the state of a task that has stopped
	bool failToChangeStatus = false;
	try
	{
		task.pause();
	} catch (...)
	{
		failToChangeStatus = true;
	}
	ASSERT_TRUE(failToChangeStatus);
	EXPECT_EQ(task.status(), Task::TaskStatus::stopped);
}


