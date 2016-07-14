/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 14, 2016
 */
#include "image.h"

mote::capture::devices::Image::Image() : _opened(false)
{ }

bool mote::capture::devices::Image::open(const std::string &filename)
{
	this->_filename = filename;
	this->_opened = boost::filesystem::exists(boost::filesystem::path(filename));
	return true;
}

bool mote::capture::devices::Image::isOpened()
{
	return this->_opened;
}

bool mote::capture::devices::Image::read(cv::Mat &image)
{
	return this->read(image, CV_LOAD_IMAGE_COLOR);
}

bool mote::capture::devices::Image::read(cv::Mat &image, int flags)
{
	image = cv::imread(this->_filename, flags);
	return image.data;
}

void mote::capture::devices::Image::close()
{
	this->_opened = false;
}