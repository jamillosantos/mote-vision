/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#ifndef MOTE_VISION_APPLICATION_HPP
#define MOTE_VISION_APPLICATION_HPP

#include <http/config.hpp>
#include <capture/devices/camera.hpp>
#include <procs/videostream.hpp>
#include <boost/log/trivial.hpp>

namespace mote
{
class Application
{
private:
	std::unique_ptr<http::Server> _server;
	std::unique_ptr<procs::VideoStream> _videoStream;
public:
	int run()
	{
		http::Config config;
		BOOST_LOG_TRIVIAL(trace) << "Starting http server at " << config.port << " ...";
		this->_server.reset(new http::Server(config));

		capture::devices::Camera camera;
		this->_videoStream.reset(new procs::VideoStream(camera));
		try
		{
			camera.open(0);
			this->_videoStream->start();
			this->_server->start();
		}
		catch (std::exception &e)
		{
			BOOST_LOG_TRIVIAL(fatal) << "Error starting HTTP Server: " << e.what();
			return 1;
		}
	}

	void stop()
	{
		BOOST_LOG_TRIVIAL(trace) << "Stopping application ...";

		if (this->_videoStream)
		{
			this->_videoStream->stop();
			this->_videoStream.reset();
		}
		if (this->_server)
		{
			this->_server->stop();
			this->_server.reset();
		}
	}
};
}

#endif //MOTE_VISION_APPLICATION_HPP
