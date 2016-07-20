/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include <boost/log/trivial.hpp>
#include "config.h"

const mote::config::Http &mote::Config::http() const
{
	return this->_http;
}

const std::vector<std::unique_ptr<mote::config::VideoStream>>& mote::Config::videoStreams() const
{
	return this->_videoStreams;
}

void mote::Config::toJson(Json::Value &json) const
{
	this->_http.toJson(json["http"]);
	json["videoStreams"] = Json::arrayValue;
	for (const std::unique_ptr<config::VideoStream>& videoStream : this->_videoStreams)
	{
		Json::Value videoStreamJson;
		videoStream->toJson(videoStreamJson);
		json["videoStreams"].append(videoStreamJson);
	}
}

void mote::Config::fromJson(const Json::Value &json)
{
	if (!json["http"].isNull())
		this->_http.fromJson(json["http"]);
	this->_videoStreams.clear();
	if (json["videoStreams"].isObject())
	{
		this->_videoStreams.emplace_back(new mote::config::VideoStream());
		this->_videoStreams.back()->fromJson(json["videoStreams"]);
	}
	else if (json["videoStreams"].isArray())
	{
		for (const Json::Value& jsonVideoStream : json["videoStreams"])
		{
			this->_videoStreams.emplace_back(new mote::config::VideoStream());
			this->_videoStreams.back()->fromJson(jsonVideoStream);
		}
	}
}
