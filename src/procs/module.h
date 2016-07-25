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
	virtual void process(VideoStream& videostream) = 0;
};
}
}

#endif //MOTE_VISION_PROCS_MODULE_H
