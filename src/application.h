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
#include <config/config.h>

namespace mote
{
class Application
{
private:
	std::unique_ptr<http::Server> _server;
	std::vector<std::unique_ptr<procs::VideoStream>> _videoStreams;
	Config _config;
public:
	virtual ~Application();

	const Config &config() const;

	/**
	 * Loads the configuration of the application from a JSON object.
	 *
	 * @return The application instance itself.
	 */
	mote::Application& config(const Json::Value &json);

	/**
	 * Runs the application initializing all the subsystems.
	 *
	 * @see mote::http::Server
	 * @see mote::procs::VideoStream
	 */
	int run();

	/**
	 * Stop the application.
	 */
	void stop();
};
}

#endif //MOTE_VISION_APPLICATION_HPP
