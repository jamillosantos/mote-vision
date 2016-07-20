/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include "http.h"

mote::config::Http::Http()
	: Http(HTTP_CONFIG_DEFAULT_ADDRESS, HTTP_CONFIG_DEFAULT_PORT, HTTP_CONFIG_DEFAULT_THREADS, HTTP_CONFIG_DEFAULT_REQUEST_TIMEOUT,
	HTTP_CONFIG_DEFAULT_CONTENT_TIMEOUT)
{ }

mote::config::Http::Http(const std::string &address, unsigned short port, unsigned long threads, long request_timeout,
	long timeout_content)
	: address(address), port(port), threads(threads), request_timeout(request_timeout), content_timeout(timeout_content)
{ }