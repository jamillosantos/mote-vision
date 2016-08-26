/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 26, 2016
 */

#ifndef MOTE_VISION_DATA_FLOODFILLSTATE_H
#define MOTE_VISION_DATA_FLOODFILLSTATE_H

#include <boost/algorithm/clamp.hpp>
#include <opencv2/core/types.hpp>
#include "pixel.h"
#include "rect.h"

namespace mote
{
namespace data
{
class FloodFillState
{
private:
	std::size_t _size;

	unsigned int _sumX;
	unsigned int _sumY;

	mote::data::Rect<int> _bBox;

	unsigned int _sumRed;
	unsigned int _sumGreen;
	unsigned int _sumBlue;
public:
	FloodFillState();

	void addPoint(const unsigned int x, const unsigned int y, const Pixel& pixel);
	void addPoint(const cv::Point2f& p, const Pixel& pixel);

	mote::data::Rect<int>& bBox();

	std::size_t size() const;

	unsigned int sumX() const;
	FloodFillState& sumX(unsigned int sumX);

	unsigned int sumY() const;
	FloodFillState& sumY(unsigned int sumY);

	int x() const;
	int y() const;

	Pixel averageColour() const;
};
}
}

#endif //MOTE_VISION_DATA_FLOODFILLSTATE_H
