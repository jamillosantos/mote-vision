/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#ifndef MOTE_VISION_CONFIG_HTTP_H
#define MOTE_VISION_CONFIG_HTTP_H

#include <string>
#include "part.h"

#define HTTP_CONFIG_DEFAULT_ADDRESS "0.0.0.0"
#define HTTP_CONFIG_DEFAULT_PORT 8080
#define HTTP_CONFIG_DEFAULT_THREADS 5
#define HTTP_CONFIG_DEFAULT_REQUEST_TIMEOUT 10
#define HTTP_CONFIG_DEFAULT_CONTENT_TIMEOUT 300

namespace mote
{
namespace config
{
class Http
	: public Part
{
public:
	Http();

	// @TODO Test this contructor
	Http(const config::Http &config)
		: Http(config.address, config.port, config.threads, config.requestTimeout, config.contentTimeout)
	{}

	Http(const std::string &address, unsigned short port, unsigned short threads, unsigned short request_timeout,
		unsigned short timeout_content);

	std::string address;

	unsigned short port;

	unsigned short threads;

	unsigned short requestTimeout;

	unsigned short contentTimeout;

	virtual void toJson(Json::Value &json) override;

	virtual void fromJson(const Json::Value &json) override;
};
}
}

#endif //MOTE_VISION_CONFIG_HTTP_H
