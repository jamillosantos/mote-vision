/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#ifndef MOTE_VISION_CONFIG_VIDEOSTREAM_H
#define MOTE_VISION_CONFIG_VIDEOSTREAM_H

#include <boost/optional.hpp>
#include "part.h"

namespace mote
{
namespace config
{
class VideoStream
	: public Part
{
public:
	std::string camera;
	boost::optional<int> width;
	boost::optional<int> height;
	boost::optional<int> saturation;
	boost::optional<int> brightness;
	boost::optional<int> contrast;
	boost::optional<int> hue;
	boost::optional<int> gain;
	boost::optional<int> exposure;

	VideoStream();

	VideoStream(const std::string& camera, const int width, const int height);

	VideoStream(const std::string& camera, const int width, const int height, const int saturation, const int brightness, const int contrast,
		const int hue, const int gain, const int exposure);

	virtual void toJson(Json::Value &json) const override;

	virtual void fromJson(const Json::Value &json) override;
};
}
}


#endif //MOTE_VISION_CONFIG_VIDEOSTREAM_H
