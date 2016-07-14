/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <capture/devices/camera.h>

GTEST_TEST(Camera, isOpened)
{
	mote::capture::devices::Camera cameraDevice;
	ASSERT_FALSE(cameraDevice.isOpened());
	if (cameraDevice.open(0))
	{
		ASSERT_TRUE(cameraDevice.isOpened());
	}
	else
	{
		//
	}
}

TEST(Camera, close)
{
	mote::capture::devices::Camera cameraDevice;
	ASSERT_FALSE(cameraDevice.isOpened());
	cameraDevice.open(0);
	ASSERT_TRUE(cameraDevice.isOpened());
	cameraDevice.close();
	ASSERT_FALSE(cameraDevice.isOpened());
}

TEST(Camera, read_frame)
{
	mote::capture::devices::Camera cameraDevice;
	if (cameraDevice.open(0))
	{
		cv::Mat image;
		ASSERT_TRUE(cameraDevice.read(image));
		cameraDevice.close();
	}
}
