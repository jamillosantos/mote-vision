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
class http_error
	: public mote::exception
{
public:
	http_error();

	http_error(const std::string &message);

	http_error(const std::exception &cause);

	http_error(const std::string &message, const std::exception &cause);
};

class already_been_flushed
	: public http_error
{
public:
	already_been_flushed();
};
}
}


#endif //MOTE_VISION_EXCEPTIONS_H
