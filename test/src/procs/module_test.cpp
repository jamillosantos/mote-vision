/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 11, 2016
 */

#include <gtest/gtest.h>
#include <procs/module.h>

class MockModule
	: public mote::procs::Module
{
public:
	int processed = 0;

	virtual const std::string &name() const override
	{
		return "name";
	}

	virtual void process(cv::Mat &in, cv::Mat &out) override
	{
		this->processed++;
	}
};

GTEST_TEST(procs_module_manager, process)
{
	MockModule* module = new MockModule();
	mote::procs::ModuleManager manager;
	cv::Mat in, out;

	manager.add(module);
	ASSERT_EQ(0, module->processed);
	manager.process(in, out);

	manager.add(module);
	manager.process(in, out);
	ASSERT_EQ(3, module->processed);
}

GTEST_TEST(procs_module_manager, process_disabled)
{
	MockModule* module = new MockModule();
	module->enabled = false;

	mote::procs::ModuleManager manager;
	cv::Mat in, out;

	manager.add(module);
	ASSERT_EQ(0, module->processed);
	manager.process(in, out);
	ASSERT_EQ(0, module->processed);
}

GTEST_TEST(procs_module_manager, size)
{
	MockModule* module1 = new MockModule();
	mote::procs::ModuleManager manager;

	ASSERT_EQ(0, manager.size());
	manager.add(module1);
	ASSERT_EQ(1, manager.size());
	manager.add(module1);
	ASSERT_EQ(2, manager.size());
}

GTEST_TEST(procs_module_manager, empty)
{
	MockModule* module1 = new MockModule();
	mote::procs::ModuleManager manager;

	ASSERT_TRUE(manager.empty());
	manager.add(module1);
	ASSERT_FALSE(manager.empty());
}

