/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 08, 2016
 */

#ifndef MOTE_VISION_CAPTURE_IMAGE_HPP
#define MOTE_VISION_CAPTURE_IMAGE_HPP

#include "device.hpp"
#include <opencv2/opencv.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace mote
{
namespace capture
{
namespace devices
{
class Image
	: public Device
{
private:
	bool _opened;
	std::string _filename;
public:
	Image()
		: _opened(false)
	{ }

	bool open(const std::string &filename)
	{
		this->_filename = filename;
		this->_opened = boost::filesystem::exists(boost::filesystem::path(filename));
		return true;
	}

	virtual bool isOpened() override
	{
		return this->_opened;
	}

	virtual bool read(cv::Mat &image) override
	{
		return this->read(image, CV_LOAD_IMAGE_COLOR);
	}

	virtual bool read(cv::Mat &image, int flags)
	{
		image = cv::imread(this->_filename, flags);
		return image.data;
	}

	virtual void close() override
	{
		this->_opened = false;
	}
};
}
}
}


#endif //MOTE_VISION_CAPTURE_IMAGE_HPP
