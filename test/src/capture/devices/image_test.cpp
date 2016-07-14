/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 09, 2016
 */

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <capture/devices/image.h>
#include "../../resources.hpp"

TEST(Image, isOpened)
{
	mote::capture::devices::Image imageDevice;
	ASSERT_FALSE(imageDevice.isOpened());
	imageDevice.open(Resources::lena().jpg().string());
	ASSERT_TRUE(imageDevice.isOpened());
}

TEST(Image, close)
{
	mote::capture::devices::Image imageDevice;
	ASSERT_FALSE(imageDevice.isOpened());
	imageDevice.open(Resources::lena().jpg().string());
	ASSERT_TRUE(imageDevice.isOpened());
	imageDevice.close();
	ASSERT_FALSE(imageDevice.isOpened());
}

TEST(Image, read_image_png)
{
	mote::capture::devices::Image imageDevice;
	imageDevice.open(Resources::lena().png().string());
	cv::Mat image;
	ASSERT_TRUE(imageDevice.read(image));
	uchar* ptr = image.ptr(0, 0);
	EXPECT_EQ(74, ptr[0]);
	EXPECT_EQ(111, ptr[1]);
	EXPECT_EQ(193, ptr[2]);
	ptr = image.ptr(208, 252);
	EXPECT_EQ(133, ptr[0]);
	EXPECT_EQ(99, ptr[1]);
	EXPECT_EQ(110, ptr[2]);
	imageDevice.close();
}

TEST(Image, read_image_jpg)
{
	mote::capture::devices::Image imageDevice;
	imageDevice.open(Resources::lena().jpg().string());
	cv::Mat image;
	ASSERT_TRUE(imageDevice.read(image));
	uchar* ptr = image.ptr(0, 0);
	EXPECT_EQ(72, ptr[0]);
	EXPECT_EQ(109, ptr[1]);
	EXPECT_EQ(191, ptr[2]);
	ptr = image.ptr(208, 252);
	EXPECT_EQ(125, ptr[0]);
	EXPECT_EQ(98, ptr[1]);
	EXPECT_EQ(107, ptr[2]);
	imageDevice.close();
}
