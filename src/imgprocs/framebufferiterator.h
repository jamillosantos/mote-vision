/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 17, 2016
 */

#ifndef MOTE_VISION_MATCVITERATOR_H
#define MOTE_VISION_MATCVITERATOR_H

#include <cstdint>
#include <data/pixel.h>
#include <opencv2/core/mat.hpp>

namespace mote
{
namespace imgprocs
{
class FrameBufferIterator
{
protected:
	unsigned int _bytesPerPixel;
	unsigned int _bytesPerLine;

	cv::Point2i _cursor;

	uint8_t* _begin;
	unsigned int _width;
	unsigned int _height;

	unsigned int _subsample;
public:
	FrameBufferIterator(unsigned int bytesPerPixel, uint8_t *begin, unsigned int width, unsigned int height,
		unsigned int subsample);

	virtual uint8_t* getAddress(const unsigned int x, const unsigned int y) = 0;

	virtual bool inBounds(const unsigned int x, const unsigned int y);

	virtual bool getPixel(mote::data::Pixel *px, const unsigned int x, const unsigned int y) = 0;
	virtual bool getPixel(mote::data::Pixel &px, const unsigned int x, const unsigned int y) = 0;

	virtual bool setPixel(const unsigned int x, const unsigned int y, mote::data::Pixel *px) = 0;
	virtual bool setPixel(const unsigned int x, const unsigned int y, const mote::data::Pixel &px) = 0;

	virtual bool go(const unsigned int x, const unsigned int y);
	virtual bool goLeft(const unsigned int amount = 1);
	virtual bool goRight(const unsigned int amount = 1);
	virtual bool goUp(const unsigned int amount = 1);
	virtual bool goDown(const unsigned int amount = 1);

	virtual void get(mote::data::Pixel *pixel);
	virtual void get(mote::data::Pixel &pixel);
};

class FramBufferIteratorRGB24
	: public FrameBufferIterator
{
public:
	FramBufferIteratorRGB24(uint8_t *begin, unsigned int width, unsigned int height, unsigned int subsample);

	virtual uint8_t *getAddress(const unsigned int x, const unsigned int y) override;

	virtual bool getPixel(mote::data::Pixel *px, const unsigned int x, const unsigned int y) override;
	virtual bool getPixel(mote::data::Pixel &px, const unsigned int x, const unsigned int y) override;

	virtual bool setPixel(const unsigned int x, const unsigned int y, mote::data::Pixel *px) override;
	virtual bool setPixel(const unsigned int x, const unsigned int y, const mote::data::Pixel &px) override;
};

template <typename T>
class MatIterator
{
private:
	T _frameBuffer;
public:
	MatIterator(cv::Mat &mat, const unsigned int subsample = 1)
		: _frameBuffer(mat.data, mat.rows, mat.cols, subsample)
	{ }

	void getPixel(mote::data::Pixel *pixel, const unsigned int x, const unsigned int y)
	{
		this->_frameBuffer->getPixel(pixel, x, y);
	}

	void getPixel(mote::data::Pixel &pixel, const unsigned int x, const unsigned int y)
	{
		this->_frameBuffer->getPixel(pixel, x, y);
	}
};

}
}

#endif //MOTE_VISION_MATCVITERATOR_H
