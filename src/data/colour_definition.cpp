/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 25, 2016
 */

#include "colour_definition.h"

mote::data::ColourRange::ColourRange(uint8_t r, uint8_t g, uint8_t b)
	: RGBColour(r, g, b)
{
	this->update();
}

mote::data::ColourRange::ColourRange(const mote::data::ColourRange &colour)
	: ColourRange(colour.r, colour.g, colour.b)
{ }

mote::data::ColourRange::ColourRange(const mote::data::RGBColour &colour)
	: ColourRange(colour.r, colour.g, colour.b)
{ }

mote::data::ColourRange::ColourRange()
	: ColourRange(0, 0, 0)
{ }

void mote::data::ColourRange::update()
{
	this->redGreen = this->r - this->g;
	this->redBlue = this->r - this->b;
	this->greenBlue = this->g - this->b;
}

mote::data::RGBColour &mote::data::ColourRange::minimum(const mote::data::RGBColour &colour)
{
	RGBColour::minimum(colour);
	const ColourRange *cr = dynamic_cast<const ColourRange*>(&colour);
	if (cr)
	{
		if (cr->redGreen < this->redGreen)
			this->redGreen = cr->redGreen;
		if (cr->redBlue < this->redBlue)
			this->redBlue = cr->redBlue;
		if (cr->greenBlue < this->greenBlue)
			this->greenBlue = cr->greenBlue;
	}
	return *this;
}

mote::data::RGBColour &mote::data::ColourRange::maximum(const mote::data::RGBColour &colour)
{
	RGBColour::maximum(colour);
	const ColourRange *cr = dynamic_cast<const ColourRange*>(&colour);
	if (cr)
	{
		if (cr->redGreen > this->redGreen)
			this->redGreen = cr->redGreen;
		if (cr->redBlue > this->redBlue)
			this->redBlue = cr->redBlue;
		if (cr->greenBlue > this->greenBlue)
			this->greenBlue = cr->greenBlue;
	}
	return *this;
}

mote::data::ColourRange mote::data::ColourRange::operator+(const mote::data::ColourRange &colour)
{
	return mote::data::ColourRange(this->r + colour.r, this->g + colour.g, this->b + colour.b);
}

mote::data::ColourRange mote::data::ColourRange::operator-(const mote::data::ColourRange &colour)
{
	return mote::data::ColourRange(this->r - colour.r, this->g - colour.g, this->b - colour.b);
}

mote::data::ColourRange mote::data::ColourRange::operator*(const mote::data::ColourRange &colour)
{
	return mote::data::ColourRange(this->r * colour.r, this->g * colour.g, this->b * colour.b);
}

mote::data::ColourRange mote::data::ColourRange::operator/(const mote::data::ColourRange &colour)
{
	return mote::data::ColourRange(this->r / colour.r, this->g / colour.g, this->b / colour.b);
}

mote::data::ColourRange &mote::data::ColourRange::operator+=(const mote::data::ColourRange &colour)
{
	this->r += colour.r;
	this->g += colour.g;
	this->b += colour.b;
	this->update();
	return *this;
}

mote::data::ColourRange &mote::data::ColourRange::operator-=(const mote::data::ColourRange &colour)
{
	this->r -= colour.r;
	this->g -= colour.g;
	this->b -= colour.b;
	this->update();
	return *this;
}

mote::data::ColourRange &mote::data::ColourRange::operator*=(const mote::data::ColourRange &colour)
{
	this->r *= colour.r;
	this->g *= colour.g;
	this->b *= colour.b;
	this->update();
	return *this;
}

mote::data::ColourRange &mote::data::ColourRange::operator/=(const mote::data::ColourRange &colour)
{
	this->r /= colour.r;
	this->g /= colour.g;
	this->b /= colour.b;
	this->update();
	return *this;
}

mote::data::ColourDefinition::ColourDefinition()
{ }

mote::data::ColourDefinition::ColourDefinition(const mote::data::ColourDefinition &definition)
	: min(definition.min), max(definition.max)
{ }

mote::data::ColourDefinition::ColourDefinition(const mote::data::ColourRange &min, const mote::data::ColourRange &max)
	: min(min), max(max)
{ }

mote::data::ColourDefinition::ColourDefinition(const mote::data::ColourRange&& min, const mote::data::ColourRange&& max)
	: min(min), max(max)
{ }

void mote::data::ColourDefinition::fromJson(const Json::Value &json)
{
	this->min.fromJson(json["min"]);
	this->max.fromJson(json["max"]);
}

void mote::data::ColourDefinition::toJson(Json::Value &json) const
{
	this->min.toJson(json["min"]);
	this->max.toJson(json["max"]);
}
