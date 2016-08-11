/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 15, 2016
 */

#include <http/actions/index.h>
#include <http/actions/camera.h>
#include <http/actions/config.h>
#include <http/actions/config/colour_definitions.h>
#include "application.h"


mote::Application::~Application()
{
	this->stop();
}

mote::Config& mote::Application::config()
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
	try
	{
		for (const std::unique_ptr<config::VideoStream>& videoStream : this->_config.videoStreams())
		{
			this->_videoStreams.emplace_back(new procs::VideoStream(*videoStream));
			this->_videoStreams.back()->start();
		}

		mote::http::actions::Index actionIndex;
		mote::http::actions::CameraSnapshot actionCameraSnapshot(this->_videoStreams);
		mote::http::actions::CameraStream actionCameraStream(this->_videoStreams);

		mote::http::actions::Config actionConfig(this->config());
		mote::http::actions::config::colour_definitions::Set actionConfigColourDefinitionsSet(this->config().colourDefinitions());
		mote::http::actions::config::colour_definitions::Clear actionConfigColourDefinitionsClear(this->config().colourDefinitions());

		this->_server.reset(new http::Server(this->_config.http()));
		this->_server->resources()["^/$"]["GET"] = std::bind(&http::actions::Index::trampolin, actionIndex,
			std::placeholders::_1, std::placeholders::_2);
		this->_server->resources()["^/camera/([0-9]+)/picture.([a-z]+)$"]["GET"] = std::bind(
			&http::actions::CameraSnapshot::trampolin, actionCameraSnapshot, std::placeholders::_1,
			std::placeholders::_2);
		this->_server->resources()["^/camera/([0-9]+)/stream.([a-z]+)$"]["GET"] = std::bind(
			&http::actions::CameraStream::trampolin, actionCameraStream, std::placeholders::_1, std::placeholders::_2);

		this->_server->resources()["^/config$"]["GET"] = std::bind(
			&http::actions::Config::trampolin, actionConfig, std::placeholders::_1, std::placeholders::_2);
		this->_server->resources()["^/config/colourDefinitions$"]["PUT"] = std::bind(
			&mote::http::actions::config::colour_definitions::Set::trampolin, actionConfigColourDefinitionsSet,
			std::placeholders::_1, std::placeholders::_2);
		this->_server->resources()["^/config/colourDefinitions/clear$"]["GET"] = std::bind(
			&mote::http::actions::config::colour_definitions::Clear::trampolin, actionConfigColourDefinitionsClear,
			std::placeholders::_1, std::placeholders::_2);
		this->_server->start();

		return 0;
	}
	catch (std::exception &e)
	{
		this->stop();
		BOOST_LOG_TRIVIAL(fatal) << "Error starting HTTP Server: " << e.what();
		return 1;
	}
}

void mote::Application::stop()
{
	if (this->_videoStreams.size())
	{
		BOOST_LOG_TRIVIAL(trace) << "Cleaning video streams ...";
		this->_videoStreams.clear();
	}

	if (this->_server)
	{
		this->_server->stop();
		this->_server.reset();
	}
}
