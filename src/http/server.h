/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#ifndef MOTE_VISION_SERVER_HPP
#define MOTE_VISION_SERVER_HPP

#include <memory>
#include <server_http.hpp>
#include <boost/log/trivial.hpp>
#include <config/http.h>
#include <server_http.hpp>
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
	config::Http _config;
public:
	Server(const config::Http& config);
	~Server();

	void start();
	void stop();
};
}
}

#endif //MOTE_VISION_SERVER_HPP
