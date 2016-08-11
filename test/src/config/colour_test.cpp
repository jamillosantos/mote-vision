/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 11, 2016
 */

#include <gtest/gtest.h>
#include <data/colour_definition.h>
#include <config/colours.h>

GTEST_TEST(config_colour_definitions, get)
{
	mote::config::ColourDefinitions cd;

	mote::data::ColourDefinition
		colourDefinition1(mote::data::ColourRange(mote::data::RGBColour::white), mote::data::ColourRange(mote::data::RGBColour::red)),
		colourDefinition2(mote::data::ColourRange(mote::data::RGBColour::green), mote::data::ColourRange(mote::data::RGBColour::blue));
	cd.add("colour1", colourDefinition1);
	cd.add("colour2", colourDefinition2);

	ASSERT_TRUE(cd.get("colour1").is_initialized());
	ASSERT_TRUE(*cd.get("colour1") == colourDefinition1);
	ASSERT_TRUE(cd.get("colour2").is_initialized());
	ASSERT_TRUE(*cd.get("colour2") == colourDefinition2);

	ASSERT_FALSE(cd.get("colour50").is_initialized());
}

GTEST_TEST(config_colour_definitions, operator_get)
{
	mote::config::ColourDefinitions cd;

	mote::data::ColourDefinition
		colourDefinition1(mote::data::ColourRange(mote::data::RGBColour::white), mote::data::ColourRange(mote::data::RGBColour::red)),
		colourDefinition2(mote::data::ColourRange(mote::data::RGBColour::green), mote::data::ColourRange(mote::data::RGBColour::blue));
	cd.add("colour1", colourDefinition1);
	cd.add("colour2", colourDefinition2);

	ASSERT_TRUE(cd["colour1"].is_initialized());
	ASSERT_TRUE(*cd["colour1"] == colourDefinition1);
	ASSERT_TRUE(cd["colour2"].is_initialized());
	ASSERT_TRUE(*cd["colour2"] == colourDefinition2);

	ASSERT_FALSE(cd["colour50"].is_initialized());
}

GTEST_TEST(config_colour_definitions, add)
{
	mote::config::ColourDefinitions cd;

	mote::data::ColourDefinition
		colourDefinition1(mote::data::ColourRange(mote::data::RGBColour::white), mote::data::ColourRange(mote::data::RGBColour::red)),
		colourDefinition2(mote::data::ColourRange(mote::data::RGBColour::green), mote::data::ColourRange(mote::data::RGBColour::blue));
	cd.add("colour1", colourDefinition1);
	cd.add("colour2", colourDefinition2);

	ASSERT_TRUE(cd.get("colour1").is_initialized());
	ASSERT_TRUE(*cd.get("colour1") == colourDefinition1);
	ASSERT_TRUE(cd.get("colour2").is_initialized());
	ASSERT_TRUE(*cd.get("colour2") == colourDefinition2);
}

GTEST_TEST(config_colour_definitions, remove)
{
	mote::config::ColourDefinitions cd;

	mote::data::ColourDefinition
		colourDefinition1(mote::data::ColourRange(mote::data::RGBColour::white), mote::data::ColourRange(mote::data::RGBColour::red)),
		colourDefinition2(mote::data::ColourRange(mote::data::RGBColour::green), mote::data::ColourRange(mote::data::RGBColour::blue));
	cd.add("colour1", colourDefinition1);
	cd.add("colour2", colourDefinition2);

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

GTEST_TEST(config_colour_definitions, find)
{
	mote::config::ColourDefinitions cd;
	mote::data::ColourDefinition
		colourDefinition1(mote::data::ColourRange(mote::data::RGBColour::white), mote::data::ColourRange(mote::data::RGBColour::red)),
		colourDefinition2(mote::data::ColourRange(mote::data::RGBColour::green), mote::data::ColourRange(mote::data::RGBColour::blue));
	cd.add("colour1", colourDefinition1);
	cd.add("colour2", colourDefinition2);

	{
		const mote::config::ColourDefinitions::const_iterator &it = cd.find("colour1");
		ASSERT_EQ(it->first, "colour1");
		ASSERT_TRUE(it->second == colourDefinition1);
	}
	{
		const mote::config::ColourDefinitions::const_iterator &it = cd.find("colour2");
		ASSERT_EQ(it->first, "colour2");
		ASSERT_TRUE(it->second == colourDefinition2);
	}
}

GTEST_TEST(config_colour_definitions, empty)
{
	mote::config::ColourDefinitions cd;
	ASSERT_TRUE(cd.empty());

	mote::data::ColourDefinition
		colourDefinition1(mote::data::ColourRange(mote::data::RGBColour::white), mote::data::ColourRange(mote::data::RGBColour::red));
	cd.add("colour1", colourDefinition1);

	ASSERT_FALSE(cd.empty());

	cd.remove("colour1");

	ASSERT_TRUE(cd.empty());
}

GTEST_TEST(config_colour_definitions, size)
{
	mote::config::ColourDefinitions cd;

	ASSERT_EQ(cd.size(), 0);

	mote::data::ColourDefinition
		colourDefinition1(mote::data::ColourRange(mote::data::RGBColour::white), mote::data::ColourRange(mote::data::RGBColour::red));
	cd.add("colour1", colourDefinition1);
	ASSERT_EQ(cd.size(), 1);

	cd.add("colour2", mote::data::ColourDefinition(mote::data::ColourRange(mote::data::RGBColour::white), mote::data::ColourRange(mote::data::RGBColour::red)));
	ASSERT_EQ(cd.size(), 2);

	cd.remove("colour1");

	ASSERT_EQ(cd.size(), 1);
}

GTEST_TEST(config_colour_definitions, toJson)
{
	mote::config::ColourDefinitions cd;
	cd.add("colour1", mote::data::ColourDefinition(mote::data::ColourRange(mote::data::RGBColour::white), mote::data::ColourRange(mote::data::RGBColour::red)));
	cd.add("colour2", mote::data::ColourDefinition(mote::data::ColourRange(mote::data::RGBColour::green), mote::data::ColourRange(mote::data::RGBColour::blue)));
	Json::Value json;
	cd.toJson(json);

	ASSERT_EQ(255, json["colour1"]["min"]["r"].asInt());
	ASSERT_EQ(255, json["colour1"]["min"]["g"].asInt());
	ASSERT_EQ(255, json["colour1"]["min"]["b"].asInt());
	ASSERT_EQ(255, json["colour1"]["max"]["r"].asInt());
	ASSERT_EQ(0, json["colour1"]["max"]["g"].asInt());
	ASSERT_EQ(0, json["colour1"]["max"]["b"].asInt());

	ASSERT_EQ(0, json["colour2"]["min"]["r"].asInt());
	ASSERT_EQ(255, json["colour2"]["min"]["g"].asInt());
	ASSERT_EQ(0, json["colour2"]["min"]["b"].asInt());
	ASSERT_EQ(0, json["colour2"]["max"]["r"].asInt());
	ASSERT_EQ(0, json["colour2"]["max"]["g"].asInt());
	ASSERT_EQ(255, json["colour2"]["max"]["b"].asInt());
}

GTEST_TEST(config_colour_definitions, fromJson)
{
	Json::Value json;

	json["colour1"]["min"]["r"] = 255;
	json["colour1"]["min"]["g"] = 255;
	json["colour1"]["min"]["b"] = 255;
	json["colour1"]["max"]["r"] = 255;
	json["colour1"]["max"]["g"] = 0;
	json["colour1"]["max"]["b"] = 0;

	json["colour2"]["min"]["r"] = 0;
	json["colour2"]["min"]["g"] = 255;
	json["colour2"]["min"]["b"] = 0;
	json["colour2"]["max"]["r"] = 0;
	json["colour2"]["max"]["g"] = 0;
	json["colour2"]["max"]["b"] = 255;

	mote::config::ColourDefinitions cd;
	cd.fromJson(json);

	ASSERT_EQ(255, cd["colour1"]->min.r);
	ASSERT_EQ(255, cd["colour1"]->min.g);
	ASSERT_EQ(255, cd["colour1"]->min.b);
	ASSERT_EQ(255, cd["colour1"]->max.r);
	ASSERT_EQ(0, cd["colour1"]->max.g);
	ASSERT_EQ(0, cd["colour1"]->max.b);

	ASSERT_EQ(0, cd["colour2"]->min.r);
	ASSERT_EQ(255, cd["colour2"]->min.g);
	ASSERT_EQ(0, cd["colour2"]->min.b);
	ASSERT_EQ(0, cd["colour2"]->max.r);
	ASSERT_EQ(0, cd["colour2"]->max.g);
	ASSERT_EQ(255, cd["colour2"]->max.b);
}

GTEST_TEST(config_colour_definitions, addJson_add)
{
	Json::Value json;

	json["colour1"]["min"]["r"] = 255;
	json["colour1"]["min"]["g"] = 255;
	json["colour1"]["min"]["b"] = 255;
	json["colour1"]["max"]["r"] = 255;
	json["colour1"]["max"]["g"] = 0;
	json["colour1"]["max"]["b"] = 0;

	json["colour2"]["min"]["r"] = 0;
	json["colour2"]["min"]["g"] = 255;
	json["colour2"]["min"]["b"] = 0;
	json["colour2"]["max"]["r"] = 0;
	json["colour2"]["max"]["g"] = 0;
	json["colour2"]["max"]["b"] = 255;

	mote::config::ColourDefinitions cd;
	cd.addJson(json);

	ASSERT_EQ(255, cd["colour1"]->min.r);
	ASSERT_EQ(255, cd["colour1"]->min.g);
	ASSERT_EQ(255, cd["colour1"]->min.b);
	ASSERT_EQ(255, cd["colour1"]->max.r);
	ASSERT_EQ(0, cd["colour1"]->max.g);
	ASSERT_EQ(0, cd["colour1"]->max.b);

	ASSERT_EQ(0, cd["colour2"]->min.r);
	ASSERT_EQ(255, cd["colour2"]->min.g);
	ASSERT_EQ(0, cd["colour2"]->min.b);
	ASSERT_EQ(0, cd["colour2"]->max.r);
	ASSERT_EQ(0, cd["colour2"]->max.g);
	ASSERT_EQ(255, cd["colour2"]->max.b);

	Json::Value json2;
	json2["colour3"]["min"]["r"] = 1;
	json2["colour3"]["min"]["g"] = 255;
	json2["colour3"]["min"]["b"] = 3;
	json2["colour3"]["max"]["r"] = 4;
	json2["colour3"]["max"]["g"] = 5;
	json2["colour3"]["max"]["b"] = 255;

	cd.addJson(json2);

	ASSERT_EQ(1, cd["colour3"]->min.r);
	ASSERT_EQ(255, cd["colour3"]->min.g);
	ASSERT_EQ(3, cd["colour3"]->min.b);
	ASSERT_EQ(4, cd["colour3"]->max.r);
	ASSERT_EQ(5, cd["colour3"]->max.g);
	ASSERT_EQ(255, cd["colour3"]->max.b);
}

GTEST_TEST(config_colour_definitions, addJson_replace)
{
	Json::Value json;

	json["colour1"]["min"]["r"] = 255;
	json["colour1"]["min"]["g"] = 255;
	json["colour1"]["min"]["b"] = 255;
	json["colour1"]["max"]["r"] = 255;
	json["colour1"]["max"]["g"] = 0;
	json["colour1"]["max"]["b"] = 0;

	json["colour2"]["min"]["r"] = 0;
	json["colour2"]["min"]["g"] = 255;
	json["colour2"]["min"]["b"] = 0;
	json["colour2"]["max"]["r"] = 0;
	json["colour2"]["max"]["g"] = 0;
	json["colour2"]["max"]["b"] = 255;

	mote::config::ColourDefinitions cd;
	cd.addJson(json);

	Json::Value json2;
	json2["colour1"]["min"]["r"] = 1;
	json2["colour1"]["min"]["g"] = 2;
	json2["colour1"]["min"]["b"] = 3;
	json2["colour1"]["max"]["r"] = 4;
	json2["colour1"]["max"]["g"] = 5;
	json2["colour1"]["max"]["b"] = 6;

	cd.addJson(json2);

	ASSERT_EQ(1, cd["colour1"]->min.r);
	ASSERT_EQ(2, cd["colour1"]->min.g);
	ASSERT_EQ(3, cd["colour1"]->min.b);
	ASSERT_EQ(4, cd["colour1"]->max.r);
	ASSERT_EQ(5, cd["colour1"]->max.g);
	ASSERT_EQ(6, cd["colour1"]->max.b);

	ASSERT_EQ(0, cd["colour2"]->min.r);
	ASSERT_EQ(255, cd["colour2"]->min.g);
	ASSERT_EQ(0, cd["colour2"]->min.b);
	ASSERT_EQ(0, cd["colour2"]->max.r);
	ASSERT_EQ(0, cd["colour2"]->max.g);
	ASSERT_EQ(255, cd["colour2"]->max.b);
}
