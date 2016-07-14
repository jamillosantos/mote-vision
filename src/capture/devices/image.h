/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 08, 2016
 */

#ifndef MOTE_VISION_CAPTURE_IMAGE_HPP
#define MOTE_VISION_CAPTURE_IMAGE_HPP

#include "device.h"
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
	Image();

	bool open(const std::string &filename);

	virtual bool isOpened() override;

	virtual bool read(cv::Mat &image) override;

	virtual bool read(cv::Mat &image, int flags);

	virtual void close() override;
};
}
}
}


#endif //MOTE_VISION_CAPTURE_IMAGE_HPP
