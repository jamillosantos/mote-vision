/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 15, 2016
 */

#ifndef MOTE_VISION_EXCEPTIONS_H
#define MOTE_VISION_EXCEPTIONS_H

#include <exception>
#include <string>
#include <boost/optional.hpp>

namespace mote
{
/**
 * Exception base class for the entire system.
 */
class exception
	: public std::exception
{
private:
	std::string _message;
	boost::optional<const std::exception&> _cause;
public:
	exception();

	exception(const std::string &message);

	exception(const std::exception& cause);

	exception(const std::string &message, const std::exception &cause);

	virtual const std::string & message() const;

	virtual const char * what() const _GLIBCXX_NOEXCEPT;
};
}


#endif //MOTE_VISION_EXCEPTIONS_H
