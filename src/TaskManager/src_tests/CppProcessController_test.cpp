

std::unique_lock<std::mutex> lock(std::mutex& mu)
{
	return std::unique_lock<std::mutex>(mu);
}


TEST(CppProcessController, testResponseToStatues)
{
	/*
		I am not actually testing multithreading here. For this reason I am only testing running and stopping.
	*/


	std::condition_variable condVar;
	std::mutex mu;
	Task::TaskStatus* statusP = new Task::TaskStatus();
	*statusP = Task::TaskStatus::running;
	double* progressP = new double();
	*progressP = -1.0;

	CppProcessController PC(
		condVar,
		mu,
		statusP,
		progressP
	);

	// Running
	{
		auto l = lock(mu);
		*statusP = Task::TaskStatus::running;
		condVar.notify_all();
	}
	ASSERT_FALSE(PC.pause_and_shouldStop());


	// stopping
	{
		auto l = lock(mu);
		*statusP = Task::TaskStatus::stopped;
		condVar.notify_all();
	}
	ASSERT_TRUE(PC.pause_and_shouldStop());

	delete statusP;
	delete progressP;
}

