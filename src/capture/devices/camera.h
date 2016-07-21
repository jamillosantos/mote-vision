/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 08, 2016
 */

#ifndef MOTE_VISION_CAMERA_HPP
#define MOTE_VISION_CAMERA_HPP

#include <opencv2/opencv.hpp>
#include "device.h"

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
	Camera();

	virtual ~Camera();

	virtual bool open(int cameraIndex);

	virtual bool open(const std::string &device);

	virtual bool isOpened() override;

	virtual bool read(cv::Mat &image) override;

	virtual void close() override;

	virtual int width();
	virtual Camera& width(int value);

	virtual int height();
	virtual Camera& height(int value);

	virtual int saturation();
	virtual Camera& saturation(int value);

	virtual int brightness();
	virtual Camera& brightness(int value);

	virtual int contrast();
	virtual Camera& contrast(int value);

	virtual int hue();
	virtual Camera& hue(int value);

	virtual int gain();
	virtual Camera& gain(int value);

	virtual int exposure();
	virtual Camera& exposure(int value);

	virtual double fps();

	virtual double realFps();
};
}
}
}


#endif //MOTE_VISION_CAMERA_HPP
