/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 30, 2016
 */

#include <gtest/gtest.h>
#include <imgprocs/segmentcolour.h>
#include <capture/devices/image.h>
#include <imgprocs/framebufferiterator.h>
#include "../resources.h"

GTEST_TEST(imgprocs_segmentcolour, action_1)
{
	mote::capture::devices::Image imageDevice;
	imageDevice.open(Resources::sprintMarker().path(1).string());
	cv::Mat in;
	ASSERT_TRUE(imageDevice.read(in));
	imageDevice.close();
	cv::Mat out;
	out = cv::Mat::zeros(in.rows, in.cols, in.type());

	mote::data::ColourDefinition colourDefinition;

	colourDefinition.min.pixel()->r = 169;
	colourDefinition.min.pixel()->g = 21;
	colourDefinition.min.pixel()->b = 118;
	colourDefinition.min.redGreen = 71;
	colourDefinition.min.redBlue = 51;
	colourDefinition.min.greenBlue = -132;

	colourDefinition.max.pixel()->r = 232;
	colourDefinition.max.pixel()->g = 101;
	colourDefinition.max.pixel()->b = 155;
	colourDefinition.max.redGreen = 208;
	colourDefinition.max.redBlue = 91;
	colourDefinition.max.greenBlue = -20;

	mote::imgprocs::SegmentColour segmentColour(320 * 320);
	std::vector<mote::data::SegmentationColourObject> results;
	segmentColour.action(in, out, 500, 10, 10, 1, colourDefinition, results);

	// out.at<cv::Vec3b>(results[0].center) = cv::Vec3b(255, 255, 255);
	// cv::imwrite("/home/jsantos/tmp/1_out.png", out);

	ASSERT_EQ(1, results.size());
	EXPECT_EQ(125, results[0].bBox.l());
	EXPECT_EQ(70, results[0].bBox.t());
	EXPECT_EQ(188, results[0].bBox.r());
	EXPECT_EQ(104, results[0].bBox.b());
	EXPECT_EQ(224, results[0].average.r);
	EXPECT_EQ(24, results[0].average.g);
	EXPECT_EQ(143, results[0].average.b);
	EXPECT_EQ(157, results[0].center.x);
	EXPECT_EQ(86, results[0].center.y);
	EXPECT_EQ(2074, results[0].size);
}

GTEST_TEST(imgprocs_segmentcolour, action_2)
{
	mote::capture::devices::Image imageDevice;
	imageDevice.open(Resources::sprintMarker().path(2).string());
	cv::Mat in;
	ASSERT_TRUE(imageDevice.read(in));
	imageDevice.close();
	cv::Mat out;
	out = cv::Mat::zeros(in.rows, in.cols, in.type());

	mote::data::ColourDefinition colourDefinition;

	colourDefinition.min.pixel()->r = 169;
	colourDefinition.min.pixel()->g = 21;
	colourDefinition.min.pixel()->b = 118;
	colourDefinition.min.redGreen = 71;
	colourDefinition.min.redBlue = 51;
	colourDefinition.min.greenBlue = -132;

	colourDefinition.max.pixel()->r = 232;
	colourDefinition.max.pixel()->g = 101;
	colourDefinition.max.pixel()->b = 155;
	colourDefinition.max.redGreen = 208;
	colourDefinition.max.redBlue = 91;
	colourDefinition.max.greenBlue = -20;

	mote::imgprocs::SegmentColour segmentColour(320 * 320);
	std::vector<mote::data::SegmentationColourObject> results;
	segmentColour.action(in, out, 500, 10, 10, 1, colourDefinition, results);

	// out.at<cv::Vec3b>(results[0].center) = cv::Vec3b(255, 255, 255);
	// cv::imwrite("/home/jsantos/tmp/2_out.png", out);

	ASSERT_EQ(1, results.size());
	EXPECT_EQ(59, results[0].bBox.l());
	EXPECT_EQ(128, results[0].bBox.t());
	EXPECT_EQ(193, results[0].bBox.r());
	EXPECT_EQ(192, results[0].bBox.b());
	EXPECT_EQ(219, results[0].average.r);
	EXPECT_EQ(23, results[0].average.g);
	EXPECT_EQ(135, results[0].average.b);
	EXPECT_EQ(127, results[0].center.x);
	EXPECT_EQ(159, results[0].center.y);
	EXPECT_EQ(7796, results[0].size);
}

GTEST_TEST(imgprocs_segmentcolour, action_3)
{
	mote::capture::devices::Image imageDevice;
	imageDevice.open(Resources::sprintMarker().path(3).string());
	cv::Mat in;
	ASSERT_TRUE(imageDevice.read(in));
	imageDevice.close();
	cv::Mat out;
	out = cv::Mat::zeros(in.rows, in.cols, in.type());

	mote::data::ColourDefinition colourDefinition;

	colourDefinition.min.pixel()->r = 169;
	colourDefinition.min.pixel()->g = 21;
	colourDefinition.min.pixel()->b = 118;
	colourDefinition.min.redGreen = 71;
	colourDefinition.min.redBlue = 51;
	colourDefinition.min.greenBlue = -132;

	colourDefinition.max.pixel()->r = 232;
	colourDefinition.max.pixel()->g = 101;
	colourDefinition.max.pixel()->b = 155;
	colourDefinition.max.redGreen = 208;
	colourDefinition.max.redBlue = 91;
	colourDefinition.max.greenBlue = -20;

	mote::imgprocs::SegmentColour segmentColour(320 * 320);
	std::vector<mote::data::SegmentationColourObject> results;
	segmentColour.action(in, out, 500, 10, 10, 1, colourDefinition, results);

	// out.at<cv::Vec3b>(results[0].center) = cv::Vec3b(255, 255, 255);
	// cv::imwrite("/home/jsantos/tmp/3_out.png", out);

	ASSERT_EQ(1, results.size());
	EXPECT_EQ(103, results[0].bBox.l());
	EXPECT_EQ(48, results[0].bBox.t());
	EXPECT_EQ(150, results[0].bBox.r());
	EXPECT_EQ(77, results[0].bBox.b());
	EXPECT_EQ(221, results[0].average.r);
	EXPECT_EQ(25, results[0].average.g);
	EXPECT_EQ(137, results[0].average.b);
	EXPECT_EQ(126, results[0].center.x);
	EXPECT_EQ(62, results[0].center.y);
	EXPECT_EQ(1273, results[0].size);
}
