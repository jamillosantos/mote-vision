/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 21, 2016
 */

#ifndef MOTE_VISION_HTTP_ACTIONS_CAMERA_H
#define MOTE_VISION_HTTP_ACTIONS_CAMERA_H

#include <http/action.h>
#include <procs/videostream.h>
#include <boost/lexical_cast.hpp>

namespace mote
{
namespace http
{
namespace actions
{
class CameraSnapshot
	: public Action
{
private:
	std::vector<std::unique_ptr<mote::procs::VideoStream>>& _streams;
public:
	CameraSnapshot(std::vector<std::unique_ptr<mote::procs::VideoStream>>& streams);
protected:
	virtual void action(mote::http::Response &response, SimpleWeb::Server<SimpleWeb::HTTP>::Request &request) override;
};
}
}
}


#endif //MOTE_VISION_HTTP_ACTIONS_CAMERA_H
