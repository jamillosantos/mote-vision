/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#ifndef MOTE_VISION_HTTP_CONFIG_HPP
#define MOTE_VISION_HTTP_CONFIG_HPP

#include <string>

#define HTTP_CONFIG_DEFAULT_PORT 8080
#define HTTP_CONFIG_DEFAULT_THREADS 5
#define HTTP_CONFIG_DEFAULT_REQUEST_TIMEOUT 10
#define HTTP_CONFIG_DEFAULT_CONTENT_TIMEOUT 300

namespace mote
{
namespace http
{
class Config
{
public:
	Config();

	Config(unsigned short port, size_t threads, long request_timeout, long timeout_content);

	unsigned short port;

	size_t threads;

	long request_timeout;

	long content_timeout;
};
}
}

#endif //MOTE_VISION_HTTP_CONFIG_HPP
