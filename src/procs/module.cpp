/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 23, 2016
 */

#include "module.h"

mote::procs::Module::Module()
	: enabled(true)
{ }

mote::procs::ModuleManager &mote::procs::ModuleManager::add(mote::procs::Module *module)
{
	this->_modules.emplace_back(module);
	return *this;
}

void mote::procs::ModuleManager::process(cv::Mat &in, cv::Mat &out)
{
	for (mote::procs::Module* module : this->_modules)
	{
		if (module->enabled)
			module->process(in, out);
	}
}

size_t mote::procs::ModuleManager::size()
{
	return this->_modules.size();
}

bool mote::procs::ModuleManager::empty()
{
	return this->_modules.empty();
}

mote::procs::ModuleManager::iterator mote::procs::ModuleManager::begin()
{
	return this->_modules.begin();
}

mote::procs::ModuleManager::iterator mote::procs::ModuleManager::end()
{
	return this->_modules.end();
}

mote::procs::ModuleManager::const_iterator mote::procs::ModuleManager::begin() const
{
	return this->_modules.begin();
}

mote::procs::ModuleManager::const_iterator mote::procs::ModuleManager::end() const
{
	return this->_modules.end();
}

mote::procs::ModuleManager::const_iterator mote::procs::ModuleManager::cbegin() const
{
	return this->_modules.cbegin();
}

mote::procs::ModuleManager::const_iterator mote::procs::ModuleManager::cend() const
{
	return this->_modules.cend();
}

mote::procs::ModuleManager::reverse_iterator mote::procs::ModuleManager::rbegin()
{
	return this->_modules.rbegin();
}

mote::procs::ModuleManager::reverse_iterator mote::procs::ModuleManager::rend()
{
	return this->_modules.rend();
}

mote::procs::ModuleManager::const_reverse_iterator mote::procs::ModuleManager::crbegin() const
{
	return this->_modules.crend();
}

mote::procs::ModuleManager::const_reverse_iterator mote::procs::ModuleManager::crend() const
{
	return this->_modules.crend();
}
