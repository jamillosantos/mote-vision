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

	Http(const std::string &address, unsigned short port, unsigned short threads, unsigned short request_timeout,
		unsigned short timeout_content);

	std::string address;

	unsigned short port;

	unsigned short threads;

	unsigned short request_timeout;

	unsigned short content_timeout;

	virtual void to_json(Json::Value &json) override;

	virtual void from_json(const Json::Value &json) override;
};
}
}

#endif //MOTE_VISION_CONFIG_HTTP_H
