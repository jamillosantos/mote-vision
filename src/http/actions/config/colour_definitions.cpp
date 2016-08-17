/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 11, 2016
 */

#include "colour_definitions.h"

mote::http::actions::config::colour_definitions::Set::Set(mote::config::ColourDefinitions &colourDefinitions)
	: _colourDefinitions(colourDefinitions)
{ }

void mote::http::actions::config::colour_definitions::Set::action(mote::http::Response &response,
	SimpleWeb::Server<SimpleWeb::HTTP>::Request &request)
{
	Json::Value
		json,
		jsonResult;
	Json::Reader reader;
	reader.parse(request.content, json, false);
	for (Json::ValueConstIterator it = json.begin(); it != json.end(); ++it)
	{
		mote::data::ColourDefinition colourDefinition;
		colourDefinition.fromJson(*it);
		this->_colourDefinitions.add(it.name(), colourDefinition);
		jsonResult[it.name()] = true;
	}
	response << jsonResult;
}

mote::http::actions::config::colour_definitions::Clear::Clear(mote::config::ColourDefinitions &colourDefinitions)
	: _colourDefinitions(colourDefinitions)
{ }

void mote::http::actions::config::colour_definitions::Clear::action(mote::http::Response &response,
	SimpleWeb::Server<SimpleWeb::HTTP>::Request &request)
{
	this->_colourDefinitions.clear();
	Json::Value jsonResult;
	jsonResult["success"] = true;
	response << jsonResult;
}

mote::http::actions::config::colour_definitions::Remove::Remove(mote::config::ColourDefinitions &colourDefinitions)
	: _colourDefinitions(colourDefinitions)
{ }

void mote::http::actions::config::colour_definitions::Remove::action(mote::http::Response &response,
	SimpleWeb::Server<SimpleWeb::HTTP>::Request &request)
{
	Json::Value
		json,
		jsonResult;
	Json::Reader reader;
	reader.parse(request.content, json);
	Json::Value &jsonColours = json["colours"];
	for (Json::ValueConstIterator it = jsonColours.begin(); it != jsonColours.end(); ++it)
	{
		this->_colourDefinitions.remove(it->asString());
		jsonResult[it->asString()] = true;
	}
	response << jsonResult;
}
