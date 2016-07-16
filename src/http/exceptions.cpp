/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 15, 2016
 */

#include "exceptions.h"

mote::http::http_error::http_error() : exception()
{ }

mote::http::http_error::http_error(const std::string &message)
	: exception(message)
{ }

mote::http::http_error::http_error(const std::exception &cause)
	: exception(cause)
{ }

mote::http::http_error::http_error(const std::string &message, const std::exception &cause)
	: exception(message, cause)
{ }

mote::http::already_been_flushed::already_been_flushed()
	: http_error("The response already flushed.")
{ }