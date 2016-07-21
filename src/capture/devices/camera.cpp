/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 14, 2016
 */

#include <boost/regex.hpp>
#include "camera.h"

mote::capture::devices::Camera::Camera() : fpsCounter(0)
{ }

mote::capture::devices::Camera::~Camera()
{
	if (this->isOpened())
		this->close();
}

bool mote::capture::devices::Camera::open(int cameraIndex)
{
	return this->videoCapture.open(cameraIndex);
}

bool mote::capture::devices::Camera::open(const std::string &device)
{
	boost::regex r("/dev/video([0-9]+)");
	boost::smatch smatch;
	if (boost::regex_search(device, smatch, r))
		return this->videoCapture.open(std::stoi(smatch[1]));
	else
		this->videoCapture.open(device);
}

bool mote::capture::devices::Camera::isOpened()
{
	return this->videoCapture.isOpened();
}

bool mote::capture::devices::Camera::read(cv::Mat &image)
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

void mote::capture::devices::Camera::close()
{
	this->videoCapture.release();
}

double mote::capture::devices::Camera::fps()
{
	return this->videoCapture.get(CV_CAP_PROP_FPS);
}

double mote::capture::devices::Camera::realFps()
{
	return this->fpsResult;
}
