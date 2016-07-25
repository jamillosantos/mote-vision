/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 24, 2016
 */

#include "colour.h"

mote::data::RGBColour mote::data::RGBColour::red(255, 0, 0);
mote::data::RGBColour mote::data::RGBColour::green(0, 255, 0);
mote::data::RGBColour mote::data::RGBColour::blue(0, 0, 255);
mote::data::RGBColour mote::data::RGBColour::white(255, 255, 255);
mote::data::RGBColour mote::data::RGBColour::black(0, 0, 0);
mote::data::RGBColour mote::data::RGBColour::yellow(255, 255, 0);
mote::data::RGBColour mote::data::RGBColour::cyan(0, 255, 255);
mote::data::RGBColour mote::data::RGBColour::magenta(255, 0, 255);

mote::data::RGBColour::RGBColour(uint8_t r, uint8_t g, uint8_t b)
	: r(r), g(g), b(b)
{ }

mote::data::RGBColour::RGBColour(const mote::data::RGBColour &colour)
	: mote::data::RGBColour::RGBColour(colour.r, colour.g, colour.b)
{ }

mote::data::RGBColour::RGBColour()
	: mote::data::RGBColour::RGBColour(0, 0, 0)
{ }

double mote::data::RGBColour::intensity()
{
	return (this->r + this->g + this->b) / 3.0;
}

mote::data::RGBColour &mote::data::RGBColour::minimum(const mote::data::RGBColour &colour)
{
	if (colour.r < this->r)
		this->r = colour.r;
	if (colour.g < this->g)
		this->g = colour.g;
	if (colour.b < this->b)
		this->b = colour.b;
	return *this;
}

mote::data::RGBColour &mote::data::RGBColour::maximum(const mote::data::RGBColour &colour)
{
	if (colour.r > this->r)
		this->r = colour.r;
	if (colour.g > g)
		this->g = colour.g;
	if (colour.b > this->b)
		this->b = colour.b;
	return *this;
}

mote::data::RGBColour &mote::data::RGBColour::operator=(const mote::data::RGBColour &colour)
{
	this->r = colour.r;
	this->g = colour.g;
	this->b = colour.b;
	return *this;
}

bool mote::data::RGBColour::operator==(const mote::data::RGBColour &colour)
{
	return
		(colour.r == this->r) &&
		(colour.g == this->g) &&
		(colour.b == this->b);
}

bool mote::data::RGBColour::operator!=(const mote::data::RGBColour &colour)
{
	return
		(colour.r != this->r) ||
		(colour.g != this->g) ||
		(colour.b != this->b);
}

mote::data::RGBColour mote::data::RGBColour::operator+(const mote::data::RGBColour &colour)
{
	return mote::data::RGBColour(this->r + colour.r, this->g + colour.g, this->b + colour.b);
}

mote::data::RGBColour mote::data::RGBColour::operator-(const mote::data::RGBColour &colour)
{
	return mote::data::RGBColour(this->r - colour.r, this->g - colour.g, this->b - colour.b);
}

mote::data::RGBColour mote::data::RGBColour::operator*(const mote::data::RGBColour &colour)
{
	return mote::data::RGBColour(this->r * colour.r, this->g * colour.g, this->b * colour.b);
}

mote::data::RGBColour mote::data::RGBColour::operator/(const mote::data::RGBColour &colour)
{
	return mote::data::RGBColour(this->r / colour.r, this->g / colour.g, this->b / colour.b);
}

mote::data::RGBColour &mote::data::RGBColour::operator+=(const mote::data::RGBColour &colour)
{
	this->r += colour.r;
	this->g += colour.g;
	this->b += colour.b;
	return *this;
}

mote::data::RGBColour &mote::data::RGBColour::operator-=(const mote::data::RGBColour &colour)
{
	this->r -= colour.r;
	this->g -= colour.g;
	this->b -= colour.b;
	return *this;
}

mote::data::RGBColour &mote::data::RGBColour::operator*=(const mote::data::RGBColour &colour)
{
	this->r *= colour.r;
	this->g *= colour.g;
	this->b *= colour.b;
	return *this;
}

mote::data::RGBColour &mote::data::RGBColour::operator/=(const mote::data::RGBColour &colour)
{
	this->r /= colour.r;
	this->g /= colour.g;
	this->b /= colour.b;
	return *this;
}

void mote::data::RGBColour::fromJson(const Json::Value &json)
{
	this->r = json["r"].asUInt();
	this->g = json["g"].asUInt();
	this->b = json["b"].asUInt();
}

void mote::data::RGBColour::toJson(Json::Value &json)
{
	json["r"] = this->r;
	json["g"] = this->g;
	json["b"] = this->b;
}
