/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#ifndef MOTE_VISION_CONFIG_HTTP_H
#define MOTE_VISION_CONFIG_HTTP_H

#include <string>

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
{
public:
	Http();

	Http(const std::string &address, unsigned short port, unsigned long threads, long request_timeout, long timeout_content);

	std::string address;

	unsigned short port;

	unsigned long threads;

	long request_timeout;

	long content_timeout;
};
}
}

#endif //MOTE_VISION_CONFIG_HTTP_H
