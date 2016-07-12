/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#ifndef MOTE_VISION_SERVER_HPP
#define MOTE_VISION_SERVER_HPP

#include <memory>
#include <server_http.hpp>
#include "../../libs/Simple-Web-Server-2.0/server_http.hpp"
#include "config.hpp"

namespace mote
{
namespace http
{
class Server
{
typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
private:
	std::unique_ptr<HttpServer> _server;
	Config _config;
public:
	Server(const Config& config)
		: _config(config)
	{ }

	~Server()
	{
		if (this->_server)
			this->stop();
	}

	void start()
	{
		this->_server.reset(new HttpServer(this->_config.port, this->_config.threads, this->_config.request_timeout, this->_config.content_timeout));

		this->_server->resource["^/"]["GET"] = [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
			std::string content = "The http server is working!";
			*response << "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
		};

		this->_server->start();
	}

	void stop()
	{
		this->_server->stop();
		this->_server.release();
	}
};
}
}

#endif //MOTE_VISION_SERVER_HPP
