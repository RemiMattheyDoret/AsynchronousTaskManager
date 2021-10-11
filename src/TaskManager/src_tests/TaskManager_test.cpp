
/*
	Definition of fixture object and the object type passed to it.
*/


// Parameter being passed to test fixture object

struct TaskManagerTester_parameters
{
	TaskManagerTester_parameters(
		std::vector<std::string> commands,
		std::vector<int>  expectedReturns,
		std::vector<bool> isExpectedExceptions
	)
	:_commands(commands), _expectedReturns(expectedReturns), _isExpectedExceptions(isExpectedExceptions)
	{
		assert(_commands.size() == expectedReturns.size());
		assert(_commands.size() == _isExpectedExceptions.size());
	}

	std::vector<std::string> _commands;
	std::vector<int> _expectedReturns;
	std::vector<bool> _isExpectedExceptions;
};


// Fixture object
struct TaskManagerTester : public testing::TestWithParam<const TaskManagerTester_parameters*>
{
protected:
	TaskManager tm;
};



/*
	Test definition
*/


TEST_P(TaskManagerTester, testSubmitSringCommands)
{
	auto as = GetParam();
	
	auto nbCommands = as->_commands.size();

	for (size_t i = 0 ; i < nbCommands ; ++i)
	{
		try
		{
			// 'EXPECT_EQ' runs only if 'submit' did not throw an exception
			EXPECT_EQ(tm.submit(as->_commands[i]), as->_expectedReturns[i]); 

			// 'ASSERT_FALSE' runs only if 'submit' did not throw an exception
			ASSERT_FALSE(as->_isExpectedExceptions[i]); 
		} catch (...)
		{
			// 'ASSERT_TRUE' runs only if 'submit' threw an exception
			ASSERT_TRUE(as->_isExpectedExceptions[i]);
		}
	}
}




/*
	Instantiation
	Do not use word wrap to read the following!
*/


TaskManagerTester_parameters A = {
	{"quit"},
	{-1},
	{false}
};


TaskManagerTester_parameters B = {
	{"   ", "quit", "quit", "1" , "start CPP a duration_5s", "quit"},
	{-1   , -1    , -1    , -1  , -1                       , -1},
	{false, false, false  , true, false                    , false}
};

TaskManagerTester_parameters C = {
	{"pause x", "start CPP a duration_50s", "   status         a "   , "start CPP ,%, duration_50s", "status ,%,"             , "start SHELL b sleep 100s", "status a"               , "pause b", "pause b", "status   a  "           , "foo", "status b"               , "status x", "resume b b", "resume bb", "resume b", "status b"               , "start SHELL x echo I love me 's/me/you/g'; sleep 10s", "pause x", "status x"              , "stop b", "quit", "pause b", "quit", "start CPP b duration_5s", "status b"               , "status x", "quit"},
	{-1       , -1                        , Task::TaskStatus::running, -1                          , Task::TaskStatus::running, -1                        , Task::TaskStatus::running, -1       , -1       , Task::TaskStatus::running, -1   ,  Task::TaskStatus::paused,  -1       , -1          , -1         , -1         , Task::TaskStatus::running, -1                                                    , -1       , Task::TaskStatus::paused, -1      , -1   , -1       , -1    , -1                       , Task::TaskStatus::running, -1        , -1},
	{true     , false                     , false                    , false                       , false                    , false                     , false                    , false    , true     ,  false                   , true ,  false                   , true      , true        , true       , false      , false                    , false                                                 , false    , false                   , false   , false, true     , false ,  false                   , false                    , true      , false}
};

TaskManagerTester_parameters D = {
	{},
	{},
	{}
};

TaskManagerTester_parameters E = {
	{"start CPP a duration_5s", "start CPP b duration_5s", "start CPP c duration_5s", "start CPP d duration_5s", "start CPP e duration_5s", "start CPP f duration_5s", "start CPP g duration_5s", "start CPP h duration_5s", "start CPP i duration_5s", "start CPP j duration_5s", "start CPP k duration_5s", "start CPP l duration_5s", "start CPP m duration_5s", "start CPP n duration_5s", "start CPP o duration_5s", "start CPP p duration_5s", "start CPP q duration_5s", "start CPP r duration_5s", "start CPP s duration_5s", "start CPP t duration_5s", "start CPP u duration_5s", "start CPP v duration_5s", "start CPP w duration_5s", "start CPP x duration_5s", "start CPP y duration_5s", "start CPP z duration_5s"},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
	{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}
};


INSTANTIATE_TEST_SUITE_P(variousCommands, TaskManagerTester, 
	testing::Values(&A,&B,&C,&D));




