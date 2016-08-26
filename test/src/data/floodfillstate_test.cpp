/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include <gtest/gtest.h>
#include <data/floodfillstate.h>
#include <data/colour.h>

GTEST_TEST(data_floodfillstate, sumX)
{
	mote::data::FloodFillState state;

	state.addPoint(1, 0, *mote::data::RGBColour::red.pixel());
	ASSERT_EQ(1, state.sumX());
	state.addPoint(2, 0, *mote::data::RGBColour::magenta.pixel());
	ASSERT_EQ(3, state.sumX());
	state.addPoint(3, 0, *mote::data::RGBColour::black.pixel());
	ASSERT_EQ(6, state.sumX());
}

GTEST_TEST(data_floodfillstate, sumY)
{
	mote::data::FloodFillState state;

	state.addPoint(0, 1, *mote::data::RGBColour::red.pixel());
	ASSERT_EQ(1, state.sumY());
	state.addPoint(0, 2, *mote::data::RGBColour::magenta.pixel());
	ASSERT_EQ(3, state.sumY());
	state.addPoint(0, 3, *mote::data::RGBColour::black.pixel());
	ASSERT_EQ(6, state.sumY());
}

GTEST_TEST(data_floodfillstate, bBox)
{
	mote::data::FloodFillState state;

	// First point
	state.addPoint(100, 50, *mote::data::RGBColour::red.pixel());
	ASSERT_EQ(100, state.bBox().x);
	ASSERT_EQ(50, state.bBox().y);
	ASSERT_EQ(0, state.bBox().width);
	ASSERT_EQ(0, state.bBox().height);
	ASSERT_EQ(100, state.bBox().r());
	ASSERT_EQ(50, state.bBox().b());

	// Stretches right
	state.addPoint(150, 50, *mote::data::RGBColour::red.pixel());
	ASSERT_EQ(100, state.bBox().x);
	ASSERT_EQ(50, state.bBox().y);
	ASSERT_EQ(50, state.bBox().width);
	ASSERT_EQ(0, state.bBox().height);
	ASSERT_EQ(150, state.bBox().r());
	ASSERT_EQ(50, state.bBox().b());

	// Stretches down
	state.addPoint(150, 200, *mote::data::RGBColour::red.pixel());
	ASSERT_EQ(100, state.bBox().x);
	ASSERT_EQ(50, state.bBox().y);
	ASSERT_EQ(50, state.bBox().width);
	ASSERT_EQ(150, state.bBox().height);
	ASSERT_EQ(150, state.bBox().r());
	ASSERT_EQ(200, state.bBox().b());

	// Stretches left
	state.addPoint(25, 200, *mote::data::RGBColour::red.pixel());
	ASSERT_EQ(25, state.bBox().x);
	ASSERT_EQ(50, state.bBox().y);
	ASSERT_EQ(125, state.bBox().width);
	ASSERT_EQ(150, state.bBox().height);
	ASSERT_EQ(150, state.bBox().r());
	ASSERT_EQ(200, state.bBox().b());

	// Stretches up
	state.addPoint(25, 15, *mote::data::RGBColour::red.pixel());
	ASSERT_EQ(25, state.bBox().x);
	ASSERT_EQ(15, state.bBox().y);
	ASSERT_EQ(125, state.bBox().width);
	ASSERT_EQ(185, state.bBox().height);
	ASSERT_EQ(150, state.bBox().r());
	ASSERT_EQ(200, state.bBox().b());
}

GTEST_TEST(data_floodfillstate, averageColour)
{
	mote::data::FloodFillState state;

	state.addPoint(1, 2, *mote::data::RGBColour::red.pixel());
	{
		mote::data::Pixel px = state.averageColour();
		ASSERT_EQ(255, px.r);
		ASSERT_EQ(0, px.g);
		ASSERT_EQ(0, px.b);
	}
	state.addPoint(1, 2, *mote::data::RGBColour::magenta.pixel());
	{
		mote::data::Pixel px = state.averageColour();
		ASSERT_EQ(255, px.r);
		ASSERT_EQ(0, px.g);
		ASSERT_EQ(255/2, px.b);
	}

	state.addPoint(1, 2, *mote::data::RGBColour::black.pixel());
	{
		mote::data::Pixel px = state.averageColour();
		ASSERT_EQ(255*2/3, px.r);
		ASSERT_EQ(0, px.g);
		ASSERT_EQ(255/3, px.b);
	}
}

GTEST_TEST(data_floodfillstate, size)
{
	mote::data::FloodFillState state;
	ASSERT_EQ(0, state.size());
	state.addPoint(0, 0, *mote::data::RGBColour::red.pixel());
	ASSERT_EQ(1, state.size());
	state.addPoint(0, 0, *mote::data::RGBColour::magenta.pixel());
	ASSERT_EQ(2, state.size());
	state.addPoint(0, 0, *mote::data::RGBColour::black.pixel());
	ASSERT_EQ(3, state.size());
}
