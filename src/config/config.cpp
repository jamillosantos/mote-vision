/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include "config.h"

void mote::Config::toJson(Json::Value &json)
{
	this->_http.toJson(json["http"]);
}

void mote::Config::fromJson(const Json::Value &json)
{
	if (!json["http"].isNull())
		this->_http.fromJson(json["http"]);
}

const mote::config::Http &mote::Config::http() const
{
	return this->_http;
}
