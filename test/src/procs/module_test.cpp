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
	bool processed = false;

	virtual const std::string &name() const override
	{
		return "name";
	}

	virtual void process(cv::Mat &in, cv::Mat &out) override
	{
		this->processed = true;
	}
};

GTEST_TEST(procs_module_manager, process)
{
	MockModule* module = new MockModule();
	mote::procs::ModuleManager manager;
	cv::Mat in, out;

	manager.add(module);
	ASSERT_FALSE(module->processed);
	manager.process(in, out);
	ASSERT_TRUE(module->processed);
}

GTEST_TEST(procs_module_manager, process_disabled)
{
	MockModule* module = new MockModule();
	module->enabled = false;

	mote::procs::ModuleManager manager;
	cv::Mat in, out;

	manager.add(module);
	ASSERT_FALSE(module->processed);
	manager.process(in, out);
	ASSERT_FALSE(module->processed);
}
