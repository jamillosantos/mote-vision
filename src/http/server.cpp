/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 14, 2016
 */
#include "server.h"

mote::http::Server::Server(const mote::http::Config& config) : _config(config)
{ }

mote::http::Server::~Server()
{
	if (this->_server)
		this->stop();
}

void mote::http::Server::start()
{
	this->_server.reset(new HttpServer(this->_config.port, this->_config.threads, this->_config.request_timeout, this->_config.content_timeout));

	this->_server->resource["^/"]["GET"] = [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
		mote::http::Response r(*response.get());
		Json::Value json;
		json["message"] = "The server is up.";
		r << json;
	};

	this->_server->start();
}

void mote::http::Server::stop()
{
	BOOST_LOG_TRIVIAL(trace) << "Stopping HTTP Server...";
	this->_server->stop();
	this->_server.release();
}