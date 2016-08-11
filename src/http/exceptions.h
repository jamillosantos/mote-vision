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
class HttpError
	: public mote::Exception
{
public:
	HttpError();

	HttpError(const std::string &message);

	HttpError(const std::exception &cause);

	HttpError(const std::string &message, const std::exception &cause);
};

class AlreadyBeenFlushed
	: public HttpError
{
public:
	AlreadyBeenFlushed();
};
}
}


#endif //MOTE_VISION_EXCEPTIONS_H
