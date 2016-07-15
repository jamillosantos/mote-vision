/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 15, 2016
 */

#include "exceptions.h"

mote::exception::exception()
{ }

mote::exception::exception(const std::string &message) : _message(message)
{ }

mote::exception::exception(const std::exception& cause) : _cause(cause)
{ }

mote::exception::exception(const std::string &message, const std::exception &cause) : _message(message), _cause(cause)
{ }

const std::string &mote::exception::message() const
{
	return this->_message;
}

const char* mote::exception::what() const _GLIBCXX_NOEXCEPT
{
	return this->_message.c_str();
}