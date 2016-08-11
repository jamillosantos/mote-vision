/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 11, 2016
 */

#include "config.h"

mote::http::actions::Config::Config(const mote::Config &config)
	: _config(config)
{ }

void mote::http::actions::Config::action(mote::http::Response &response,
	SimpleWeb::Server<SimpleWeb::HTTP>::Request &request)
{
	Json::Value json;
	this->_config.toJson(json);
	response << json;
}
