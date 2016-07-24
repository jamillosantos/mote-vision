/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 22, 2016
 */

#ifndef MOTE_VISION_HTTP_ACTIONS_VIDEOSTREAM_H
#define MOTE_VISION_HTTP_ACTIONS_VIDEOSTREAM_H

#include <http/action.h>
#include <procs/videostream.h>

namespace mote
{
namespace http
{
namespace actions
{
class VideoStream
	: public Action
{
protected:
	std::vector<std::unique_ptr<mote::procs::VideoStream>>& _streams;
public:
	VideoStream(std::vector<std::unique_ptr<mote::procs::VideoStream>>& streams);
};
}
}
}

#endif //MOTE_VISION_HTTP_ACTIONS_VIDEOSTREAM_H
