/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 21, 2016
 */

#ifndef MOTE_VISION_HTTP_ACTIONS_CAMERA_H
#define MOTE_VISION_HTTP_ACTIONS_CAMERA_H

#include <http/action.h>
#include <procs/videostream.h>
#include <boost/lexical_cast.hpp>
#include "videostream.h"

#define CAMERASTREAM_BOUNDARY "donotcross"

namespace mote
{
namespace http
{
namespace actions
{
class CameraSnapshot
	: public mote::http::actions::VideoStream
{
public:
	CameraSnapshot(std::vector<std::unique_ptr<procs::VideoStream>> &streams);
protected:
	virtual void action(mote::http::Response &response, SimpleWeb::Server<SimpleWeb::HTTP>::Request &request) override;
};

class CameraStream
	: public mote::http::actions::VideoStream
{
public:
	CameraStream(std::vector<std::unique_ptr<procs::VideoStream>> &streams);

	virtual void trampolin(std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response,
		std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request) override;

protected:
	virtual void action(mote::http::Response &response, SimpleWeb::Server<SimpleWeb::HTTP>::Request &request) override;
};
}
}
}


#endif //MOTE_VISION_HTTP_ACTIONS_CAMERA_H
