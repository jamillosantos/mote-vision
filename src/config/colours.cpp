/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 04, 2016
 */

#include "colours.h"

void mote::config::ColourDefinitions::add(const std::string &name, const mote::data::ColourDefinition &colourDefinition)
{
	const iterator &it = this->_colours.find(name);
	if (it == this->_colours.end())
		this->_colours.insert(std::make_pair(name, colourDefinition));
	else
		this->_colours[name] = colourDefinition;
}

void mote::config::ColourDefinitions::remove(const std::string &name)
{
	this->_colours.erase(name);
}

bool mote::config::ColourDefinitions::exists(const std::string &name) const
{
	return (this->_colours.find(name) != this->_colours.end());
}

mote::config::ColourDefinitions::const_iterator mote::config::ColourDefinitions::find(const std::string &name) const
{
	return this->_colours.find(name);
}

bool mote::config::ColourDefinitions::empty() const
{
	return this->_colours.empty();
}

size_t mote::config::ColourDefinitions::size() const
{
	return this->_colours.size();
}

boost::optional<mote::data::ColourDefinition> mote::config::ColourDefinitions::get(const std::string &name) const
{
	const const_iterator &it = this->find(name);
	if (it == this->end())
		return boost::optional<mote::data::ColourDefinition>();
	else
		return it->second;
}

boost::optional<mote::data::ColourDefinition> mote::config::ColourDefinitions::operator[](const std::string &name) const
{
	return this->get(name);
}

mote::config::ColourDefinitions::iterator mote::config::ColourDefinitions::begin()
{
	return this->_colours.begin();
}

mote::config::ColourDefinitions::iterator mote::config::ColourDefinitions::end()
{
	return this->_colours.end();
}

mote::config::ColourDefinitions::const_iterator mote::config::ColourDefinitions::begin() const
{
	return this->_colours.begin();
}

mote::config::ColourDefinitions::const_iterator mote::config::ColourDefinitions::cbegin() const
{
	return this->_colours.cbegin();
}

mote::config::ColourDefinitions::const_iterator mote::config::ColourDefinitions::end() const
{
	return this->_colours.end();
}

mote::config::ColourDefinitions::const_iterator mote::config::ColourDefinitions::cend() const
{
	return this->_colours.cend();
}

mote::config::ColourDefinitions::reverse_iterator mote::config::ColourDefinitions::rbegin()
{
	return this->_colours.rbegin();
}

mote::config::ColourDefinitions::reverse_iterator mote::config::ColourDefinitions::rend()
{
	return this->_colours.rend();
}

mote::config::ColourDefinitions::const_reverse_iterator mote::config::ColourDefinitions::crbegin() const
{
	return this->_colours.crbegin();
}

mote::config::ColourDefinitions::const_reverse_iterator mote::config::ColourDefinitions::crend() const
{
	return this->_colours.crend();
}

void mote::config::ColourDefinitions::toJson(Json::Value &json) const
{
	for (const pair& colourDefinition : this->_colours)
	{
		const std::string &name = colourDefinition.first;
		colourDefinition.second.toJson(json[name]);
	}
}

void mote::config::ColourDefinitions::fromJson(const Json::Value &json)
{
	this->_colours.clear();
	this->addJson(json);
}

void mote::config::ColourDefinitions::addJson(const Json::Value &json)
{
	for (Json::Value::const_iterator it = json.begin(); it != json.end(); ++it)
	{
		mote::data::ColourDefinition tmp;
		tmp.fromJson(it.key());
	}
}
