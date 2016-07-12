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

	time_t fpsStart;
	time_t fpsEnd;
	double fpsResult;
	unsigned long fpsCounter;
public:
	Camera()
		: fpsCounter(0)
	{ }

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
		if (fpsCounter == 0)
		{
			time(&this->fpsStart);
		}
		bool result = this->videoCapture.read(image);
		time(&this->fpsEnd);
		double sec = difftime(this->fpsEnd, this->fpsStart);
		this->fpsCounter ++;
		if (sec >= 1)
		{
			this->fpsResult = (this->fpsCounter / sec);
			if (this->fpsCounter > 1000)
			{
				this->fpsCounter = 0;
				time(&this->fpsStart);
			}
		}
		return result;
	}

	virtual void close() override
	{
		this->videoCapture.release();
	}

	virtual double fps()
	{
		return this->videoCapture.get(CV_CAP_PROP_FPS);
	}

	virtual double realFps()
	{
		return this->fpsResult;
	}
};
}
}
}


#endif //MOTE_VISION_CAMERA_HPP
