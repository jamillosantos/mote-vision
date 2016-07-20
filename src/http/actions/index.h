/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#ifndef MOTE_VISION_HTTP_ACTIONS_INDEX_H
#define MOTE_VISION_HTTP_ACTIONS_INDEX_H

#include <http/action.h>

namespace mote
{
namespace http
{
namespace actions
{
class Index
	: public Action
{
protected:
	virtual void action(mote::http::Response &response, SimpleWeb::Server<SimpleWeb::HTTP>::Request &request) override;
};
}
}
}


#endif //MOTE_VISION_HTTP_ACTIONS_INDEX_H
