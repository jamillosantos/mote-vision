/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 11, 2016
 */

#include <gtest/gtest.h>
#include <data/colour_definition.h>
#include <config/colours.h>

GTEST_TEST(config_colour_definitions, add)
{
	mote::config::ColourDefinitions cd;
	cd.add("colour1", mote::data::ColourDefinition(mote::data::ColourRange(mote::data::RGBColour::white), mote::data::ColourRange(mote::data::RGBColour::red)));
	cd.add("colour2", mote::data::ColourDefinition(mote::data::ColourRange(mote::data::RGBColour::green), mote::data::ColourRange(mote::data::RGBColour::blue)));
	ASSERT_TRUE(cd.get("colour1").is_initialized());
	ASSERT_TRUE(cd.get("colour1")->min == mote::data::RGBColour::white);
	ASSERT_TRUE(cd.get("colour1")->max == mote::data::RGBColour::red);
	ASSERT_TRUE(cd.get("colour2").is_initialized());
	ASSERT_TRUE(cd.get("colour2")->min == mote::data::RGBColour::green);
	ASSERT_TRUE(cd.get("colour2")->max == mote::data::RGBColour::blue);
}

GTEST_TEST(config_colour_definitions, remove)
{
	mote::config::ColourDefinitions cd;
	cd.add("colour1", mote::data::ColourDefinition(mote::data::ColourRange(mote::data::RGBColour::white), mote::data::ColourRange(mote::data::RGBColour::red)));
	cd.add("colour2", mote::data::ColourDefinition(mote::data::ColourRange(mote::data::RGBColour::green), mote::data::ColourRange(mote::data::RGBColour::blue)));
	ASSERT_TRUE(cd.exists("colour1"));
	ASSERT_TRUE(cd.exists("colour2"));
	cd.remove("colour1");
	ASSERT_FALSE(cd.exists("colour1"));
	ASSERT_TRUE(cd.exists("colour2"));
	cd.remove("colour2");
	ASSERT_FALSE(cd.exists("colour1"));
}


GTEST_TEST(config_colour_definitions, exists)
{
	mote::config::ColourDefinitions cd;
	cd.add("colour1", mote::data::ColourDefinition(mote::data::ColourRange(mote::data::RGBColour::white), mote::data::ColourRange(mote::data::RGBColour::red)));
	cd.add("colour2", mote::data::ColourDefinition(mote::data::ColourRange(mote::data::RGBColour::green), mote::data::ColourRange(mote::data::RGBColour::blue)));
	ASSERT_TRUE(cd.exists("colour1"));
	ASSERT_TRUE(cd.exists("colour2"));
	ASSERT_FALSE(cd.exists("colour3"));
	cd.remove("colour1");
	ASSERT_FALSE(cd.exists("colour1"));
	ASSERT_TRUE(cd.exists("colour2"));
	cd.add("colour3", mote::data::ColourDefinition(mote::data::ColourRange(mote::data::RGBColour::cyan), mote::data::ColourRange(mote::data::RGBColour::magenta)));
	ASSERT_TRUE(cd.exists("colour3"));
}


