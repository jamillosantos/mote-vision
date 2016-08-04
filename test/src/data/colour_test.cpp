/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include <gtest/gtest.h>
#include <data/colour.h>

GTEST_TEST(data_colour, constructor_with_params)
{
	mote::data::RGBColour colour(0, 1, 2);
	ASSERT_EQ(0, colour.r);
	ASSERT_EQ(1, colour.g);
	ASSERT_EQ(2, colour.b);
}

GTEST_TEST(data_colour, constructor_with_no_params)
{
	mote::data::RGBColour colour;
	ASSERT_EQ(0, colour.r);
	ASSERT_EQ(0, colour.g);
	ASSERT_EQ(0, colour.b);
}

GTEST_TEST(data_colour, constructor_copy)
{
	mote::data::RGBColour
		colour1(1, 2, 3),
		colour2(colour1);
	ASSERT_EQ(colour1.r, colour2.r);
	ASSERT_EQ(colour1.g, colour2.g);
	ASSERT_EQ(colour1.b, colour2.b);
}

GTEST_TEST(data_colour, intesity)
{
	mote::data::RGBColour colour1(0, 255, 0);
	ASSERT_EQ(85, colour1.intensity());
}

GTEST_TEST(data_colour, operator_equals)
{
	mote::data::RGBColour
		colour1(0, 1, 2),
		colour2(0, 1, 2);
	ASSERT_TRUE(colour1 == colour2);
}

GTEST_TEST(data_colour, operator_not_equal)
{
	mote::data::RGBColour
		colour1(0, 1, 2),
		colour2(1, 1, 2),
		colour3(0, 2, 2),
		colour4(0, 1, 3),
		colour5(3, 3, 3);
	ASSERT_TRUE(colour1 != colour2);
	ASSERT_TRUE(colour1 != colour3);
	ASSERT_TRUE(colour1 != colour4);
	ASSERT_TRUE(colour1 != colour5);
}

GTEST_TEST(data_colour, operator_plus)
{
	mote::data::RGBColour
		colour1(10, 20, 30),
		colour2(1, 2, 3),
		result(11, 22, 33);
	ASSERT_TRUE(result == (colour1 + colour2));
}

GTEST_TEST(data_colour, operator_minus)
{
	mote::data::RGBColour
		colour1(10, 20, 30),
		colour2(1, 2, 3),
		result(9, 18, 27);
	ASSERT_TRUE(result == (colour1 - colour2));
}

GTEST_TEST(data_colour, operator_multiply)
{
	mote::data::RGBColour
		colour1(10, 20, 30),
		colour2(2, 3, 4),
		result(20, 60, 120);
	ASSERT_TRUE(result == (colour1 * colour2));
}

GTEST_TEST(data_colour, operator_divide)
{
	mote::data::RGBColour
		colour1(10, 21, 40),
		colour2(2, 3, 4),
		result(5, 7, 10);
	ASSERT_TRUE(result == (colour1 / colour2));
}

GTEST_TEST(data_colour, operator_plus_assign)
{
	mote::data::RGBColour
		colour1(10, 20, 30),
		colour2(1, 2, 3),
		result(11, 22, 33);
	colour1 += colour2;
	ASSERT_TRUE(result == colour1);
}

GTEST_TEST(data_colour, operator_minus_assign)
{
	mote::data::RGBColour
		colour1(10, 20, 30),
		colour2(1, 2, 3),
		result(9, 18, 27);
	colour1 -= colour2;
	ASSERT_TRUE(result == colour1);
}

GTEST_TEST(data_colour, operator_multiply_assign)
{
	mote::data::RGBColour
		colour1(10, 20, 30),
		colour2(2, 3, 4),
		result(20, 60, 120);
	colour1 *= colour2;
	ASSERT_TRUE(result == colour1);
}

GTEST_TEST(data_colour, operator_divide_assign)
{
	mote::data::RGBColour
		colour1(10, 21, 40),
		colour2(2, 3, 4),
		result(5, 7, 10);
	colour1 /= colour2;
	ASSERT_TRUE(result == colour1);
}

GTEST_TEST(data_colour, maximum)
{
	mote::data::RGBColour
		colourBase(10, 20, 30),
		colour(10, 20, 30),
		colour2(11, 2, 3),
		colour2Result(11, 20, 30),
		colour3(1, 22, 3),
		colour3Result(10, 22, 30),
		colour4(1, 2, 33),
		colour4Result(10, 20, 33);

	colour.maximum(colour2);
	ASSERT_TRUE(colour2Result == colour);

	colour = colourBase;
	colour.maximum(colour3);
	ASSERT_TRUE(colour3Result == colour);

	colour = colourBase;
	colour.maximum(colour4);
	ASSERT_TRUE(colour4Result == colour);
}

GTEST_TEST(data_colour, minimum)
{
	mote::data::RGBColour
		colourBase(10, 20, 30),
		colour(10, 20, 30),
		colour2(1, 22, 33),
		colour2Result(1, 20, 30),
		colour3(11, 2, 33),
		colour3Result(10, 2, 30),
		colour4(11, 22, 3),
		colour4Result(10, 20, 3);

	colour.minimum(colour2);
	ASSERT_TRUE(colour2Result == colour);

	colour = colourBase;
	colour.minimum(colour3);
	ASSERT_TRUE(colour3Result == colour);

	colour = colourBase;
	colour.minimum(colour4);
	ASSERT_TRUE(colour4Result == colour);
}
