/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#ifndef MOTE_VISION_HTTP_ACTION_H
#define MOTE_VISION_HTTP_ACTION_H

#include <server_http.hpp>
#include "response.h"

namespace mote
{
namespace http
{
/**
 * Method that is called from the `http::Server`.
 */
class Action
{
public:
	virtual void trampolin(std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response,
		std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request);
protected:
	virtual void action(mote::http::Response& response, SimpleWeb::Server<SimpleWeb::HTTP>::Request& request) = 0;
};
}
}


#endif //MOTE_VISION_HTTP_ACTION_H
