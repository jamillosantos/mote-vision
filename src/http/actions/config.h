/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 11, 2016
 */

#ifndef MOTE_VISION_HTTP_ACTIONS_CONFIG_H
#define MOTE_VISION_HTTP_ACTIONS_CONFIG_H

#include <http/action.h>
#include <config/config.h>

namespace mote
{
namespace http
{
namespace actions
{
class Config
	: public Action
{
private:
	const mote::Config &_config;
public:
	Config(const mote::Config &config);
protected:
	virtual void action(mote::http::Response &response, SimpleWeb::Server<SimpleWeb::HTTP>::Request &request) override;
};
}
}
}

#endif //MOTE_VISION_HTTP_ACTIONS_CONFIG_H
