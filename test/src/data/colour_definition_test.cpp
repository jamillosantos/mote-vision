/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include <gtest/gtest.h>
#include <data/colour_definition.h>

GTEST_TEST(data_colour_definition, constructor_with_params)
{
	mote::data::ColourRange colour(0, 1, 2);
	ASSERT_EQ(0, colour.r);
	ASSERT_EQ(1, colour.g);
	ASSERT_EQ(2, colour.b);
}

GTEST_TEST(data_colour_definition, constructor_with_no_params)
{
	mote::data::ColourRange colour;
	ASSERT_EQ(0, colour.r);
	ASSERT_EQ(0, colour.g);
	ASSERT_EQ(0, colour.b);
}

GTEST_TEST(data_colour_definition, operator_equals)
{
	mote::data::ColourRange
		colour1(0, 1, 2),
		colour2(0, 1, 2);
	ASSERT_TRUE(colour1 == colour2);
}

GTEST_TEST(data_colour_definition, operator_not_equal)
{
	mote::data::ColourRange
		colour1(0, 1, 2),
		colour2(1, 1, 2),
		colour3(0, 2, 2),
		colour4(0, 1, 3);
	ASSERT_TRUE(colour1 != colour2);
	ASSERT_TRUE(colour1 != colour3);
	ASSERT_TRUE(colour1 != colour4);
}

GTEST_TEST(data_colour_definition, operator_plus)
{
	mote::data::ColourRange
		colour1(10, 20, 30),
		colour2(1, 2, 3),
		result(11, 22, 33),
		value = (colour1 + colour2);
	ASSERT_TRUE(result == value);
	ASSERT_EQ(value.redGreen, (value.r - value.g));
	ASSERT_EQ(value.redBlue, (value.r - value.b));
	ASSERT_EQ(value.greenBlue, (value.g - value.b));
}

GTEST_TEST(data_colour_definition, operator_minus)
{
	mote::data::ColourRange
		colour1(10, 20, 30),
		colour2(1, 2, 3),
		result(9, 18, 27),
		value = (colour1 - colour2);
	ASSERT_TRUE(result == value);
	ASSERT_EQ(value.redGreen, (value.r - value.g));
	ASSERT_EQ(value.redBlue, (value.r - value.b));
	ASSERT_EQ(value.greenBlue, (value.g - value.b));
}

GTEST_TEST(data_colour_definition, operator_multiply)
{
	mote::data::ColourRange
		colour1(10, 20, 30),
		colour2(2, 3, 4),
		result(20, 60, 120),
		value = (colour1 * colour2);
	ASSERT_TRUE(result == value);
	ASSERT_EQ(value.redGreen, (value.r - value.g));
	ASSERT_EQ(value.redBlue, (value.r - value.b));
	ASSERT_EQ(value.greenBlue, (value.g - value.b));
}

GTEST_TEST(data_colour_definition, operator_divide)
{
	mote::data::ColourRange
		colour1(10, 21, 40),
		colour2(2, 3, 4),
		result(5, 7, 10),
		value = (colour1 / colour2);
	ASSERT_TRUE(result == value);
	ASSERT_EQ(value.redGreen, (value.r - value.g));
	ASSERT_EQ(value.redBlue, (value.r - value.b));
	ASSERT_EQ(value.greenBlue, (value.g - value.b));
}

GTEST_TEST(data_colour_definition, operator_plus_assign)
{
	mote::data::ColourRange
		colour1(10, 20, 30),
		colour2(1, 2, 3),
		result(11, 22, 33);
	colour1 += colour2;
	ASSERT_TRUE(result == colour1);
	ASSERT_EQ(colour1.redGreen, (colour1.r - colour1.g));
	ASSERT_EQ(colour1.redBlue, (colour1.r - colour1.b));
	ASSERT_EQ(colour1.greenBlue, (colour1.g - colour1.b));
}

GTEST_TEST(data_colour_definition, operator_minus_assign)
{
	mote::data::ColourRange
		colour1(10, 20, 30),
		colour2(1, 2, 3),
		result(9, 18, 27);
	colour1 -= colour2;
	ASSERT_TRUE(result == colour1);
	ASSERT_EQ(colour1.redGreen, (colour1.r - colour1.g));
	ASSERT_EQ(colour1.redBlue, (colour1.r - colour1.b));
	ASSERT_EQ(colour1.greenBlue, (colour1.g - colour1.b));
}

GTEST_TEST(data_colour_definition, operator_multiply_assign)
{
	mote::data::ColourRange
		colour1(10, 20, 30),
		colour2(2, 3, 4),
		result(20, 60, 120);
	colour1 *= colour2;
	ASSERT_TRUE(result == colour1);
	ASSERT_EQ(colour1.redGreen, (colour1.r - colour1.g));
	ASSERT_EQ(colour1.redBlue, (colour1.r - colour1.b));
	ASSERT_EQ(colour1.greenBlue, (colour1.g - colour1.b));
}

GTEST_TEST(data_colour_definition, operator_divide_assign)
{
	mote::data::ColourRange
		colour1(10, 21, 40),
		colour2(2, 3, 4),
		result(5, 7, 10);
	colour1 /= colour2;
	ASSERT_TRUE(result == colour1);
	ASSERT_EQ(colour1.redGreen, (colour1.r - colour1.g));
	ASSERT_EQ(colour1.redBlue, (colour1.r - colour1.b));
	ASSERT_EQ(colour1.greenBlue, (colour1.g - colour1.b));
}

GTEST_TEST(data_colour_definition, maximum)
{
	mote::data::ColourRange
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

GTEST_TEST(data_colour_definition, minimum)
{
	mote::data::ColourRange
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
