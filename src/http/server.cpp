/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 14, 2016
 */
#include <http/actions/index.h>
#include "server.h"

mote::http::Server::Server(const mote::config::Http& config)
	: _config(config), _server(new HttpServer(this->_config.port, this->_config.threads, this->_config.requestTimeout,
		this->_config.contentTimeout))
{ }

mote::http::Server::~Server()
{
	if (this->_server)
		this->stop();
}

std::unordered_map<std::string, std::unordered_map<
	std::string,
	std::function<void(
		std::shared_ptr<typename SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response>,
		std::shared_ptr<typename SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request>
	)>>
>& mote::http::Server::resources()
{
	return this->_server->resource;
}

void mote::http::Server::start()
{
	BOOST_LOG_TRIVIAL(trace) << "Starting http server at " << this->_config.port << " ...";
	this->_server->start();
}

void mote::http::Server::stop()
{
	BOOST_LOG_TRIVIAL(trace) << "Stopping HTTP Server...";
	this->_server->stop();
	this->_server.release();
}
