/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 25, 2016
 */

#ifndef MOTE_VISION_COLOUR_DEFINITION_H
#define MOTE_VISION_COLOUR_DEFINITION_H

#include "colour.h"

namespace mote
{
namespace data
{
/**
 * Colour range definition for aalab colour detection method.
 */
class ColourRange
	: public RGBColour
{
public:
	ColourRange(uint8_t r, uint8_t g, uint8_t b);
	ColourRange(const ColourRange &colour);
	ColourRange();

	/**
	 * Red - green.
	 */
	int redGreen;

	/**
	 * Red - blue.
	 */
	int redBlue;

	/**
	 * Green - blue.
	 */
	int greenBlue;

	virtual RGBColour& minimum(const RGBColour &colour) override;
	virtual RGBColour& maximum(const RGBColour &colour) override;

	virtual void update();

	ColourRange operator+(const ColourRange& colour);
	ColourRange operator-(const ColourRange& colour);
	ColourRange operator*(const ColourRange& colour);
	ColourRange operator/(const ColourRange& colour);

	virtual ColourRange& operator+=(const ColourRange& colour);
	virtual ColourRange& operator-=(const ColourRange& colour);
	virtual ColourRange& operator*=(const ColourRange& colour);
	virtual ColourRange& operator/=(const ColourRange& colour);
};

class ColourDefinition
{
public:
	ColourRange max;
	ColourRange min;
};
}
}

#endif //MOTE_VISION_COLOUR_DEFINITION_H