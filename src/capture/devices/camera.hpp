/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 08, 2016
 */

#ifndef MOTE_VISION_CAMERA_HPP
#define MOTE_VISION_CAMERA_HPP

#include <opencv2/opencv.hpp>
#include "device.hpp"

namespace mote
{
namespace capture
{
namespace devices
{
class Camera
	: public Device
{
private:
	cv::VideoCapture videoCapture;
public:
	virtual ~Camera()
	{
		if (this->isOpened())
			this->close();
	}

	virtual bool open(int cameraIndex)
	{
		return this->videoCapture.open(cameraIndex);
	}

	virtual bool isOpened() override
	{
		return this->videoCapture.isOpened();
	}

	virtual bool read(cv::Mat &image) override
	{
		return this->videoCapture.read(image);
	}

	virtual void close() override
	{
		this->videoCapture.release();
	}
};
}
}
}


#endif //MOTE_VISION_CAMERA_HPP
