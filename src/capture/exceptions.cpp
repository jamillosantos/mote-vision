/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include "exceptions.h"

mote::capture::CannotOpenDevice::CannotOpenDevice(const std::string &device)
	: exception("Cannot open '" + device + "'.")
{}
