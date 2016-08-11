/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 15, 2016
 */

#include "exceptions.h"

mote::http::HttpError::HttpError() : Exception()
{ }

mote::http::HttpError::HttpError(const std::string &message)
	: Exception(message)
{ }

mote::http::HttpError::HttpError(const std::exception &cause)
	: Exception(cause)
{ }

mote::http::HttpError::HttpError(const std::string &message, const std::exception &cause)
	: Exception(message, cause)
{ }

mote::http::AlreadyBeenFlushed::AlreadyBeenFlushed()
	: HttpError("The response already flushed.")
{ }