/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include "videostream.h"

void mote::config::VideoStream::toJson(Json::Value &json) const
{
	json["camera"] = this->camera;
	if (this->width)
		json["width"] = *this->width;
	if (this->height)
		json["height"] = *this->height;
	if (this->saturation)
		json["saturation"] = *this->saturation;
	if (this->brightness)
		json["brightness"] = *this->brightness;
	if (this->contrast)
		json["contrast"] = *this->contrast;
	if (this->hue)
		json["hue"] = *this->hue;
	if (this->gain)
		json["gain"] = *this->gain;
	if (this->exposure)
		json["exposure"] = *this->exposure;
}

void mote::config::VideoStream::fromJson(const Json::Value &json)
{
	this->camera = json["camera"].asString();
	if (!json["width"].isNull())
		this->width = json["width"].asInt();
	if (!json["height"].isNull())
		this->height = json["height"].asInt();
	if (!json["saturation"].isNull())
		this->saturation = json["saturation"].asInt();
	if (!json["brightness"].isNull())
		this->brightness = json["brightness"].asInt();
	if (!json["contrast"].isNull())
		this->contrast = json["contrast"].asInt();
	if (!json["hue"].isNull())
		this->hue = json["hue"].asInt();
	if (!json["gain"].isNull())
		this->gain = json["gain"].asInt();
	if (!json["exposure"].isNull())
		this->exposure = json["exposure"].asInt();
}

mote::config::VideoStream::VideoStream()
{ }

mote::config::VideoStream::VideoStream(const std::string& camera, const int width, const int height)
	: camera(camera), width(width), height(height)
{ }

mote::config::VideoStream::VideoStream(const std::string& camera, const int width, const int height, const int saturation,
	const int brightness, const int contrast, const int hue, const int gain, const int exposure)
	: camera(camera), width(width), height(height), saturation(saturation), brightness(brightness), contrast(contrast), hue(hue),
	  gain(gain), exposure(exposure)
{}
