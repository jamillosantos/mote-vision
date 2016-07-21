/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#ifndef MOTE_VISION_CAPTURE_EXCEPTIONS_H
#define MOTE_VISION_CAPTURE_EXCEPTIONS_H

#include "../exceptions.h"

namespace mote
{
namespace capture
{
class CannotOpenDevice
	: public mote::exception
{
public:
	CannotOpenDevice(const std::string &device);
};
}
}

#endif //MOTE_VISION_CAPTURE_EXCEPTIONS_H
