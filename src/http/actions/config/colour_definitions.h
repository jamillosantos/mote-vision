/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 11, 2016
 */

#ifndef MOTE_VISION_COLOUR_DEFINITIONS_H
#define MOTE_VISION_COLOUR_DEFINITIONS_H

#include <http/action.h>
#include <config/colours.h>
#include <json/reader.h>

namespace mote
{
namespace http
{
namespace actions
{
namespace config
{
namespace colour_definitions
{
class Set
	: public Action
{
private:
	mote::config::ColourDefinitions &_colourDefinitions;
public:
	Set(mote::config::ColourDefinitions &colourDefinitions);
protected:
	virtual void action(mote::http::Response &response, SimpleWeb::Server<SimpleWeb::HTTP>::Request &request) override;
};

class Clear
	: public Action
{
private:
	mote::config::ColourDefinitions &_colourDefinitions;
public:
	Clear(mote::config::ColourDefinitions &colourDefinitions);
protected:
	virtual void action(mote::http::Response &response, SimpleWeb::Server<SimpleWeb::HTTP>::Request &request) override;
};
}
}
}
}
}

#endif //MOTE_VISION_COLOUR_DEFINITIONS_H
