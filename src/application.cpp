/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 15, 2016
 */

#include "application.h"

const mote::Config& mote::Application::config() const
{
	return this->_config;
}

mote::Application& mote::Application::config(const Json::Value &json)
{
	this->_config.fromJson(json);
	return *this;
}

int mote::Application::run()
{
	BOOST_LOG_TRIVIAL(trace) << "Starting http server at " << this->_config.http().port << " ...";
	this->_server.reset(new http::Server(this->_config.http()));

	capture::devices::Camera camera;
	this->_videoStream.reset(new procs::VideoStream(camera));
	try
	{
		camera.open(0);
		this->_videoStream->start();
		this->_server->start();
		return 0;
	}
	catch (std::exception &e)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Error starting HTTP Server: " << e.what();
		return 1;
	}
}

void mote::Application::stop()
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
