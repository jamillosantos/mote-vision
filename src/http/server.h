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
	config::Http _config;
	std::unique_ptr<HttpServer> _server;
public:
	Server(const config::Http& config);
	~Server();

	std::unordered_map<std::string, std::unordered_map<
		std::string,
		std::function<void(
			std::shared_ptr<typename SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response>,
			std::shared_ptr<typename SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request>
		)>>
	>& resources();

	void start();
	void stop();
};
}
}

#endif //MOTE_VISION_SERVER_HPP
