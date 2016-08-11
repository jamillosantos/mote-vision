/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 23, 2016
 */

#ifndef MOTE_VISION_PROCS_MODULE_H
#define MOTE_VISION_PROCS_MODULE_H

#include "videostream.h"

namespace mote
{
namespace procs
{
class Module
{
public:
	Module();

	/**
	 * Flag for checking whether the modules is enabled or not.
	 */
	bool enabled;

	/**
	 * Name of the module. Used for identifying the module inside of an future list.
	 * @return Name of the module.
	 */
	virtual const std::string& name() const = 0;

	/**
	 * Performs the processing of the module over the framebuffer.
	 *
	 * @param in Input framebuffer.
	 * @param out Output framebuffer, post processed.
	 */
	virtual void process(cv::Mat &in, cv::Mat &out) = 0;
};

/**
 * Manager of the modules.
 */
class ModuleManager
{
private:
	typedef std::vector<std::unique_ptr<Module>> vector;
public:
	typedef vector::iterator iterator;
	typedef vector::reverse_iterator reverse_iterator;
	typedef vector::const_iterator const_iterator;
	typedef vector::const_reverse_iterator const_reverse_iterator;
private:
	vector _modules;
public:
	/**
	 * Ads a module into the manager.
	 *
	 * @param module Module that will be added.
	 * @return The ModuleManager instance itself.
	 */
	ModuleManager& add(Module* module);

	/**
	 * Iterate over all modules and call its `process` for the enabled ones.
	 *
	 * @param in The input framebuffer.
	 * @param out The output framebuffer. After processing.
	 */
	virtual void process(cv::Mat& in, cv::Mat& out);

	/**
	 * Number of modules inside of this manager.
	 *
	 * @return
	 */
	size_t size();

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();

	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;
};
}
}

#endif //MOTE_VISION_PROCS_MODULE_H
