/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 15, 2016
 */

#ifndef MOTE_VISION_HTTP_EXCEPTIONS_H
#define MOTE_VISION_HTTP_EXCEPTIONS_H

#include <exceptions.h>

namespace mote
{
namespace http
{
class HttpException
	: public mote::Exception
{
public:
	HttpException();

	HttpException(const std::string &message);

	HttpException(const std::exception &cause);

	HttpException(const std::string &message, const std::exception &cause);
};

class HttpError
	: public HttpException
{
private:
	int _errorCode;
public:
	HttpError(const int errorCode, const std::string &message);

	int errorCode() const;
};

class AlreadyBeenFlushed
	: public HttpException
{
public:
	AlreadyBeenFlushed();
};
}
}


#endif //MOTE_VISION_EXCEPTIONS_H
