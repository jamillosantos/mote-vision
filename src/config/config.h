/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#ifndef MOTE_VISION_CONFIG_H
#define MOTE_VISION_CONFIG_H

#include <memory>
#include "http.h"
#include "videostream.h"
#include "colours.h"

namespace mote
{
class Config
	: public config::Part
{
private:
	config::Http _http;
	std::vector<std::unique_ptr<config::VideoStream>> _videoStreams;
	mote::config::ColourDefinitions _colourDefinitions;
public:
	const config::Http &http() const;

	const std::vector<std::unique_ptr<config::VideoStream>> &videoStreams() const;

	const mote::config::ColourDefinitions &colourDefinitions() const;

	virtual void toJson(Json::Value &json) const override;

	virtual void fromJson(const Json::Value &json) override;
};
}


#endif //MOTE_VISION_CONFIG_H
