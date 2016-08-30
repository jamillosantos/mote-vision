/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include <gtest/gtest.h>
#include <data/pixel.h>

GTEST_TEST(data_pixel, constructor)
{
	mote::data::Pixel p(1, 2, 3);
	ASSERT_EQ(1, p.r);
	ASSERT_EQ(2, p.g);
	ASSERT_EQ(3, p.b);
}

GTEST_TEST(data_pixel, size_of)
{
	ASSERT_EQ(3, sizeof(mote::data::Pixel));
}

GTEST_TEST(data_pixel, address_alignment)
{
	char* data = "\x03\x02\x01";
	mote::data::Pixel *p = (mote::data::Pixel*)data;
	ASSERT_EQ(1, p->r);
	ASSERT_EQ(2, p->g);
	ASSERT_EQ(3, p->b);
}

GTEST_TEST(data_pixel, is)
{
	mote::data::Pixel pixel(1, 2, 3);
	ASSERT_TRUE(pixel.is(1, 2, 3));
}
