/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 26, 2016
 */

#ifndef MOTE_VISION_RECT_H
#define MOTE_VISION_RECT_H

#include <opencv2/core/types.hpp>

namespace mote
{
namespace data
{
template <typename T>
class Rect
	: public cv::Rect_<T>
{
public:
	Rect()
	{ }

	Rect(T _x, T _y, T _width, T _height)
		: cv::Rect_<T>(_x, _y, _width, _height)
	{ }

	Rect(const cv::Rect_<T> &r)
		: cv::Rect_<T>(r)
	{ }

	Rect(const cv::Point_<T> &org, const cv::Size_<T> &sz)
		: cv::Rect_<T>(org, sz)
	{ }

	Rect(const cv::Point_<T> &pt1, const cv::Point_<T> &pt2)
		: cv::Rect_<T>(pt1, pt2)
	{ }

	T r() const
	{
		return this->x + this->width;
	}

	Rect<T>& r(const T r)
	{
		this->width = r - this->x;
		return *this;
	}

	T b() const
	{
		return this->y + this->height;
	}

	Rect<T>& b(const T b)
	{
		this->height = b - this->y;
		return *this;
	}
};
}
}


#endif //MOTE_VISION_RECT_H
