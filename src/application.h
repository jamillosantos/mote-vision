/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#ifndef MOTE_VISION_APPLICATION_HPP
#define MOTE_VISION_APPLICATION_HPP

#include <capture/devices/camera.h>
#include <procs/videostream.h>
#include <boost/log/trivial.hpp>
#include <http/server.h>

namespace mote
{
class Application
{
private:
	std::unique_ptr<http::Server> _server;
	std::unique_ptr<procs::VideoStream> _videoStream;
public:
	int run();

	void stop();
};
}

#endif //MOTE_VISION_APPLICATION_HPP
