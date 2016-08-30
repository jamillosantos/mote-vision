/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 17, 2016
 */

#include "pixel.h"

mote::data::Pixel::Pixel()
{ }

mote::data::Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b)
	: b(b), g(g), r(r)
{ }


mote::data::Pixel::Pixel(const mote::data::Pixel &px)
	: b(px.b), g(px.g), r(px.r)
{

}

bool mote::data::Pixel::is(uint8_t r, uint8_t g, uint8_t b)
{
	return
		(this->r == r)
		&& (this->g == g)
		&& (this->b == b);
}
