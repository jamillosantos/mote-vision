/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include <gtest/gtest.h>
#include <data/rect.h>

GTEST_TEST(data_rect, get_r)
{
	mote::data::Rect<float>
		rect1(10.0f, 0.0f, 100.0f, 0.0f),
		rect2(11.0f, 0.0f, 99.0f, 0.0f),
		rect3(12.0f, 0.0f, 2.0f, 0.0f);
	ASSERT_EQ(110.0f, rect1.r());
	ASSERT_EQ(110.0f, rect2.r());
	ASSERT_EQ(14.0f, rect3.r());
}

GTEST_TEST(data_rect, set_r)
{
	mote::data::Rect<float> rect(10.0f, 0.0f, 100.0f, 0.0f);
	ASSERT_EQ(110.0f, rect.r());
	rect.r(0.0f);
	ASSERT_EQ(-10.0f, rect.width);
	rect.r(8.0f);
	ASSERT_EQ(-2.0f, rect.width);
	rect.r(80.0f);
	ASSERT_EQ(70.0f, rect.width);
}

GTEST_TEST(data_rect, get_b)
{
	mote::data::Rect<float>
		rect1(0.0f, 10.0f, 0.0f, 100.0f),
		rect2(0.0f, 11.0f, 0.0f, 99.0f),
		rect3(0.0f, 12.0f, 0.0f, 2.0f);
	ASSERT_EQ(110.0f, rect1.b());
	ASSERT_EQ(110.0f, rect2.b());
	ASSERT_EQ(14.0f, rect3.b());
}

GTEST_TEST(data_rect, set_b)
{
	mote::data::Rect<float> rect(0.0f, 10.0f, 0.0f, 100.0f);
	ASSERT_EQ(110.0f, rect.b());
	rect.b(0.0f);
	ASSERT_EQ(-10.0f, rect.height);
	rect.b(8.0f);
	ASSERT_EQ(-2.0f, rect.height);
	rect.b(80.0f);
	ASSERT_EQ(70.0f, rect.height);
}

GTEST_TEST(data_rect, movesX)
{
	mote::data::Rect<float> rect(40.0f, 50.0f, 60.0f, 50.0f);
	rect.movesX(0.0f);
	ASSERT_EQ(100.0f, rect.width);
	rect.movesX(20.0f);
	ASSERT_EQ(80.0f, rect.width);
	rect.movesX(100.0f);
	ASSERT_EQ(0.0f, rect.width);
	rect.movesX(110.0f);
	ASSERT_EQ(-10.0f, rect.width);
}

GTEST_TEST(data_rect, movesY)
{
	mote::data::Rect<float> rect(40.0f, 50.0f, 60.0f, 50.0f);
	rect.movesY(0.0f);
	ASSERT_EQ(100.0f, rect.height);
	rect.movesY(20.0f);
	ASSERT_EQ(80.0f, rect.height);
	rect.movesY(100.0f);
	ASSERT_EQ(0.0f, rect.height);
	rect.movesY(110.0f);
	ASSERT_EQ(-10.0f, rect.height);
}
