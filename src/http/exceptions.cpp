/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 15, 2016
 */

#include "exceptions.h"

mote::http::HttpException::HttpException() : Exception()
{ }

mote::http::HttpException::HttpException(const std::string &message)
	: Exception(message)
{ }

mote::http::HttpException::HttpException(const std::exception &cause)
	: Exception(cause)
{ }

mote::http::HttpException::HttpException(const std::string &message, const std::exception &cause)
	: Exception(message, cause)
{ }

mote::http::AlreadyBeenFlushed::AlreadyBeenFlushed()
	: HttpException("The response already flushed.")
{ }

mote::http::HttpError::HttpError(const int errorCode, const std::string &message)
	: HttpException(message), _errorCode(errorCode)
{ }

int mote::http::HttpError::errorCode() const
{
	return this->_errorCode;
}
