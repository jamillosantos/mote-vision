/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 24, 2016
 */

#ifndef MOTE_VISION_COLOUR_H
#define MOTE_VISION_COLOUR_H

#include <cstdint>

#include "serializable.h"

namespace mote
{
namespace data
{
class Colour
	: public Serializable
{
};

class RGBColour
	: public Colour
{
public:
	static RGBColour red;
	static RGBColour blue;
	static RGBColour green;
	static RGBColour white;
	static RGBColour black;
	static RGBColour yellow;
	static mote::data::RGBColour cyan;
	static mote::data::RGBColour magenta;
public:
	RGBColour(uint8_t r, uint8_t g, uint8_t b);
	RGBColour(const RGBColour& colour);
	RGBColour();

	uint8_t r;
	uint8_t g;
	uint8_t b;

	virtual double intensity();

	bool operator==(const RGBColour& colour);
	bool operator!=(const RGBColour& colour);

	RGBColour operator+(const RGBColour& colour);
	RGBColour operator-(const RGBColour& colour);
	RGBColour operator*(const RGBColour& colour);
	RGBColour operator/(const RGBColour& colour);

	RGBColour &operator+=(const RGBColour& colour);
	RGBColour &operator-=(const RGBColour& colour);
	RGBColour &operator*=(const RGBColour& colour);
	RGBColour &operator/=(const RGBColour& colour);

	virtual void fromJson(const Json::Value &json) override;

	virtual void toJson(Json::Value &json) override;
};
}
}


#endif //MOTE_VISION_COLOUR_H
