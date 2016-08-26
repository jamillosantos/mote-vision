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
	: ColourRange(colour.pixel()->r, colour.pixel()->g, colour.pixel()->b)
{ }

mote::data::ColourRange::ColourRange(const mote::data::RGBColour &colour)
	: ColourRange(colour.pixel()->r, colour.pixel()->g, colour.pixel()->b)
{ }

mote::data::ColourRange::ColourRange()
	: ColourRange(0, 0, 0)
{ }

void mote::data::ColourRange::update()
{
	this->redGreen = this->pixel()->r - this->pixel()->g;
	this->redBlue = this->pixel()->r - this->pixel()->b;
	this->greenBlue = this->pixel()->g - this->pixel()->b;
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
	return mote::data::ColourRange(this->pixel()->r + colour.pixel()->r, this->pixel()->g + colour.pixel()->g, this->pixel()->b + colour.pixel()->b);
}

mote::data::ColourRange mote::data::ColourRange::operator-(const mote::data::ColourRange &colour)
{
	return mote::data::ColourRange(this->pixel()->r - colour.pixel()->r, this->pixel()->g - colour.pixel()->g, this->pixel()->b - colour.pixel()->b);
}

mote::data::ColourRange mote::data::ColourRange::operator*(const mote::data::ColourRange &colour)
{
	return mote::data::ColourRange(this->pixel()->r * colour.pixel()->r, this->pixel()->g * colour.pixel()->g, this->pixel()->b * colour.pixel()->b);
}

mote::data::ColourRange mote::data::ColourRange::operator/(const mote::data::ColourRange &colour)
{
	return mote::data::ColourRange(this->pixel()->r / colour.pixel()->r, this->pixel()->g / colour.pixel()->g, this->pixel()->b / colour.pixel()->b);
}

mote::data::ColourRange &mote::data::ColourRange::operator+=(const mote::data::ColourRange &colour)
{
	this->pixel()->r += colour.pixel()->r;
	this->pixel()->g += colour.pixel()->g;
	this->pixel()->b += colour.pixel()->b;
	this->update();
	return *this;
}

mote::data::ColourRange &mote::data::ColourRange::operator-=(const mote::data::ColourRange &colour)
{
	this->pixel()->r -= colour.pixel()->r;
	this->pixel()->g -= colour.pixel()->g;
	this->pixel()->b -= colour.pixel()->b;
	this->update();
	return *this;
}

mote::data::ColourRange &mote::data::ColourRange::operator*=(const mote::data::ColourRange &colour)
{
	this->pixel()->r *= colour.pixel()->r;
	this->pixel()->g *= colour.pixel()->g;
	this->pixel()->b *= colour.pixel()->b;
	this->update();
	return *this;
}

mote::data::ColourRange &mote::data::ColourRange::operator/=(const mote::data::ColourRange &colour)
{
	this->pixel()->r /= colour.pixel()->r;
	this->pixel()->g /= colour.pixel()->g;
	this->pixel()->b /= colour.pixel()->b;
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

bool mote::data::ColourDefinition::operator==(const mote::data::ColourDefinition &colourDefinition) const
{
	return
		(this->min == colourDefinition.min) && (this->max == colourDefinition.max);
}

bool mote::data::ColourDefinition::operator!=(const mote::data::ColourDefinition &colourDefinition) const
{
	return !(colourDefinition == *this);
}
