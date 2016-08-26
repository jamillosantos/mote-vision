/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include <gtest/gtest.h>
#include <data/colour_definition.h>

GTEST_TEST(data_colour_range, constructor_with_params)
{
	mote::data::ColourRange colour(0, 1, 2);
	ASSERT_EQ(0, colour.pixel()->r);
	ASSERT_EQ(1, colour.pixel()->g);
	ASSERT_EQ(2, colour.pixel()->b);
}

GTEST_TEST(data_colour_range, constructor_with_no_params)
{
	mote::data::ColourRange colour;
	ASSERT_EQ(0, colour.pixel()->r);
	ASSERT_EQ(0, colour.pixel()->g);
	ASSERT_EQ(0, colour.pixel()->b);
}

GTEST_TEST(data_colour_range, constructor_copy)
{
	mote::data::ColourRange
		colour1(1, 2, 3),
		colour2(colour1);
	ASSERT_EQ(colour1.pixel()->r, colour2.pixel()->r);
	ASSERT_EQ(colour1.pixel()->g, colour2.pixel()->g);
	ASSERT_EQ(colour1.pixel()->b, colour2.pixel()->b);
	ASSERT_EQ(colour1.redBlue, colour2.redBlue);
	ASSERT_EQ(colour1.redGreen, colour2.redGreen);
	ASSERT_EQ(colour1.greenBlue, colour2.greenBlue);
}

GTEST_TEST(data_colour_range, constructor_rgbcolour)
{
	mote::data::RGBColour colour(1, 2, 3);
	mote::data::ColourRange colourRange(colour);

	ASSERT_EQ(colour.pixel()->r, colourRange.pixel()->r);
	ASSERT_EQ(colour.pixel()->g, colourRange.pixel()->g);
	ASSERT_EQ(colour.pixel()->b, colourRange.pixel()->b);
}

GTEST_TEST(data_colour_range, operator_equals)
{
	mote::data::ColourRange
		colour1(0, 1, 2),
		colour2(0, 1, 2);
	ASSERT_TRUE(colour1 == colour2);
}

GTEST_TEST(data_colour_range, operator_not_equal)
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

GTEST_TEST(data_colour_range, operator_plus)
{
	mote::data::ColourRange
		colour1(10, 20, 30),
		colour2(1, 2, 3),
		result(11, 22, 33),
		value = (colour1 + colour2);
	ASSERT_TRUE(result == value);
	ASSERT_EQ(value.redGreen, (value.pixel()->r - value.pixel()->g));
	ASSERT_EQ(value.redBlue, (value.pixel()->r - value.pixel()->b));
	ASSERT_EQ(value.greenBlue, (value.pixel()->g - value.pixel()->b));
}

GTEST_TEST(data_colour_range, operator_minus)
{
	mote::data::ColourRange
		colour1(10, 20, 30),
		colour2(1, 2, 3),
		result(9, 18, 27),
		value = (colour1 - colour2);
	ASSERT_TRUE(result == value);
	ASSERT_EQ(value.redGreen, (value.pixel()->r - value.pixel()->g));
	ASSERT_EQ(value.redBlue, (value.pixel()->r - value.pixel()->b));
	ASSERT_EQ(value.greenBlue, (value.pixel()->g - value.pixel()->b));
}

GTEST_TEST(data_colour_range, operator_multiply)
{
	mote::data::ColourRange
		colour1(10, 20, 30),
		colour2(2, 3, 4),
		result(20, 60, 120),
		value = (colour1 * colour2);
	ASSERT_TRUE(result == value);
	ASSERT_EQ(value.redGreen, (value.pixel()->r - value.pixel()->g));
	ASSERT_EQ(value.redBlue, (value.pixel()->r - value.pixel()->b));
	ASSERT_EQ(value.greenBlue, (value.pixel()->g - value.pixel()->b));
}

GTEST_TEST(data_colour_range, operator_divide)
{
	mote::data::ColourRange
		colour1(10, 21, 40),
		colour2(2, 3, 4),
		result(5, 7, 10),
		value = (colour1 / colour2);
	ASSERT_TRUE(result == value);
	ASSERT_EQ(value.redGreen, (value.pixel()->r - value.pixel()->g));
	ASSERT_EQ(value.redBlue, (value.pixel()->r - value.pixel()->b));
	ASSERT_EQ(value.greenBlue, (value.pixel()->g - value.pixel()->b));
}

GTEST_TEST(data_colour_range, operator_plus_assign)
{
	mote::data::ColourRange
		colour1(10, 20, 30),
		colour2(1, 2, 3),
		result(11, 22, 33);
	colour1 += colour2;
	ASSERT_TRUE(result == colour1);
	ASSERT_EQ(colour1.redGreen, (colour1.pixel()->r - colour1.pixel()->g));
	ASSERT_EQ(colour1.redBlue, (colour1.pixel()->r - colour1.pixel()->b));
	ASSERT_EQ(colour1.greenBlue, (colour1.pixel()->g - colour1.pixel()->b));
}

GTEST_TEST(data_colour_range, operator_minus_assign)
{
	mote::data::ColourRange
		colour1(10, 20, 30),
		colour2(1, 2, 3),
		result(9, 18, 27);
	colour1 -= colour2;
	ASSERT_TRUE(result == colour1);
	ASSERT_EQ(colour1.redGreen, (colour1.pixel()->r - colour1.pixel()->g));
	ASSERT_EQ(colour1.redBlue, (colour1.pixel()->r - colour1.pixel()->b));
	ASSERT_EQ(colour1.greenBlue, (colour1.pixel()->g - colour1.pixel()->b));
}

GTEST_TEST(data_colour_range, operator_multiply_assign)
{
	mote::data::ColourRange
		colour1(10, 20, 30),
		colour2(2, 3, 4),
		result(20, 60, 120);
	colour1 *= colour2;
	ASSERT_TRUE(result == colour1);
	ASSERT_EQ(colour1.redGreen, (colour1.pixel()->r - colour1.pixel()->g));
	ASSERT_EQ(colour1.redBlue, (colour1.pixel()->r - colour1.pixel()->b));
	ASSERT_EQ(colour1.greenBlue, (colour1.pixel()->g - colour1.pixel()->b));
}

GTEST_TEST(data_colour_range, operator_divide_assign)
{
	mote::data::ColourRange
		colour1(10, 21, 40),
		colour2(2, 3, 4),
		result(5, 7, 10);
	colour1 /= colour2;
	ASSERT_TRUE(result == colour1);
	ASSERT_EQ(colour1.redGreen, (colour1.pixel()->r - colour1.pixel()->g));
	ASSERT_EQ(colour1.redBlue, (colour1.pixel()->r - colour1.pixel()->b));
	ASSERT_EQ(colour1.greenBlue, (colour1.pixel()->g - colour1.pixel()->b));
}

GTEST_TEST(data_colour_range, maximum)
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

GTEST_TEST(data_colour_range, minimum)
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

GTEST_TEST(data_colour_definition, constructor_copy)
{
	mote::data::ColourDefinition
		colourDefinition1(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(4, 5, 6)),
		colourDefinition2(colourDefinition1);
	ASSERT_TRUE(colourDefinition1.min == colourDefinition2.min);
	ASSERT_TRUE(colourDefinition1.max == colourDefinition2.max);
}

GTEST_TEST(data_colour_definition, operator_equal)
{
	mote::data::ColourDefinition
		colourDefinition1(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(4, 5, 6)),
		colourDefinition2(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(4, 5, 6));
	ASSERT_TRUE(colourDefinition1 == colourDefinition2);
}

GTEST_TEST(data_colour_definition, operator_not_equal)
{
	{	// Min.r different
		mote::data::ColourDefinition
			colourDefinition1(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(4, 5, 6)),
			colourDefinition2(mote::data::ColourRange(10, 2, 3), mote::data::ColourRange(4, 5, 6));
		ASSERT_TRUE(colourDefinition1 != colourDefinition2);
	}

	{	// Min.g different
		mote::data::ColourDefinition
			colourDefinition1(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(4, 5, 6)),
			colourDefinition2(mote::data::ColourRange(1, 20, 3), mote::data::ColourRange(4, 5, 6));
		ASSERT_TRUE(colourDefinition1 != colourDefinition2);
	}

	{	// Min.b different
		mote::data::ColourDefinition
			colourDefinition1(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(4, 5, 6)),
			colourDefinition2(mote::data::ColourRange(1, 2, 30), mote::data::ColourRange(4, 5, 6));
		ASSERT_TRUE(colourDefinition1 != colourDefinition2);
	}

	{	// Max.r different
		mote::data::ColourDefinition
			colourDefinition1(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(4, 5, 6)),
			colourDefinition2(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(40, 5, 6));
		ASSERT_TRUE(colourDefinition1 != colourDefinition2);
	}

	{	// Max.g different
		mote::data::ColourDefinition
			colourDefinition1(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(4, 5, 6)),
			colourDefinition2(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(4, 50, 6));
		ASSERT_TRUE(colourDefinition1 != colourDefinition2);
	}

	{	// Max.b different
		mote::data::ColourDefinition
			colourDefinition1(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(4, 5, 6)),
			colourDefinition2(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(4, 5, 60));
		ASSERT_TRUE(colourDefinition1 != colourDefinition2);
	}
}

GTEST_TEST(data_colour_definition, toJson)
{
	mote::data::ColourDefinition colourDefinition(mote::data::ColourRange(1, 2, 3), mote::data::ColourRange(4, 5, 6));
	Json::Value json;
	colourDefinition.toJson(json);
	ASSERT_EQ(1, json["min"]["r"].asInt());
	ASSERT_EQ(2, json["min"]["g"].asInt());
	ASSERT_EQ(3, json["min"]["b"].asInt());
	ASSERT_EQ(4, json["max"]["r"].asInt());
	ASSERT_EQ(5, json["max"]["g"].asInt());
	ASSERT_EQ(6, json["max"]["b"].asInt());
}

GTEST_TEST(data_colour_definition, fromJson)
{
	mote::data::ColourDefinition colourDefinition;
	Json::Value json;
	json["min"]["r"] = 1;
	json["min"]["g"] = 2;
	json["min"]["b"] = 3;
	json["max"]["r"] = 4;
	json["max"]["g"] = 5;
	json["max"]["b"] = 6;
	colourDefinition.fromJson(json);
	ASSERT_EQ(1, colourDefinition.min.pixel()->r);
	ASSERT_EQ(2, colourDefinition.min.pixel()->g);
	ASSERT_EQ(3, colourDefinition.min.pixel()->b);
	ASSERT_EQ(4, colourDefinition.max.pixel()->r);
	ASSERT_EQ(5, colourDefinition.max.pixel()->g);
	ASSERT_EQ(6, colourDefinition.max.pixel()->b);
}
