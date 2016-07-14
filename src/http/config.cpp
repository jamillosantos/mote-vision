/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 14, 2016
 */

#include "config.h"

mote::http::Config::Config() : Config(HTTP_CONFIG_DEFAULT_PORT, HTTP_CONFIG_DEFAULT_THREADS, HTTP_CONFIG_DEFAULT_REQUEST_TIMEOUT,
	HTTP_CONFIG_DEFAULT_CONTENT_TIMEOUT)
{ }

mote::http::Config::Config(unsigned short port, size_t threads, long request_timeout, long timeout_content)
	: port(port), threads(threads), request_timeout(request_timeout), content_timeout(timeout_content)
{ }