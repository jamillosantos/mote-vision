/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 15, 2016
 */

#include "exceptions.h"

mote::Exception::Exception()
{ }

mote::Exception::Exception(const std::string &message) : _message(message)
{ }

mote::Exception::Exception(const std::exception& cause) : _cause(cause)
{ }

mote::Exception::Exception(const std::string &message, const std::exception &cause) : _message(message), _cause(cause)
{ }

const std::string &mote::Exception::message() const
{
	return this->_message;
}

const char* mote::Exception::what() const _GLIBCXX_NOEXCEPT
{
	return this->_message.c_str();
}