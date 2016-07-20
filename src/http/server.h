/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#ifndef MOTE_VISION_SERVER_HPP
#define MOTE_VISION_SERVER_HPP

#include <memory>
#include <server_http.hpp>
#include <boost/log/trivial.hpp>
#include "../../libs/Simple-Web-Server-2.0/server_http.hpp"
#include "config.h"
#include "response.h"

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
	Server(const Config& config);

	~Server();

	void start();

	void stop();
};
}
}

#endif //MOTE_VISION_SERVER_HPP
