/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 08, 2016
 */

#ifndef MOTE_VISION_CAPTURE_DEVICE_HPP
#define MOTE_VISION_CAPTURE_DEVICE_HPP

#include <opencv/ml.h>

namespace mote
{
namespace capture
{
class Device
{
public:
	/**
	 * Reads a frame from the device.
	 */
	virtual bool read(cv::Mat &image) = 0;

	/**
	 * Return if the device is open.
	 */
	virtual bool isOpened() = 0;

	/**
	 * Closes the device and release the device.
	 */
	virtual void close() = 0;
};
}
}


#endif //MOTE_VISION_CAPTURE_DEVICE_HPP
