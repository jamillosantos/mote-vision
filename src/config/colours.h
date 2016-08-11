/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 04, 2016
 */

#ifndef MOTE_VISION_COLOURS_H
#define MOTE_VISION_COLOURS_H

#include <data/colour_definition.h>
#include <memory>
#include <boost/optional.hpp>
#include "part.h"

namespace mote
{
namespace config
{
class ColourDefinitions
	: public Part
{
public:
	typedef std::map<std::string, mote::data::ColourDefinition> map;
	typedef std::pair<std::string, mote::data::ColourDefinition> pair;
	typedef map::iterator iterator;
	typedef map::const_iterator const_iterator;
	typedef map::reverse_iterator reverse_iterator;
	typedef map::const_reverse_iterator const_reverse_iterator;
private:
	map _colours;
public:
	void add(const std::string &name, const mote::data::ColourDefinition& colourDefinition);
	void remove(const std::string &name);

	bool exists(const std::string &name) const;
	const_iterator find(const std::string &name) const;

	bool empty() const;
	size_t size() const;

	boost::optional<mote::data::ColourDefinition> get(const std::string &name) const;
	boost::optional<mote::data::ColourDefinition> operator[](const std::string &name) const;

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator cbegin() const;
	const_iterator end() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

	virtual void toJson(Json::Value &json) const override;

	virtual void fromJson(const Json::Value &json) override;
	virtual void addJson(const Json::Value &json);
};
}
}


#endif //MOTE_VISION_COLOURS_H
