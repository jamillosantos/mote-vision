/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include <gtest/gtest.h>
#include <json/value.h>
#include <config/config.h>

#define CONFIG_HTTP_ADDRESS "1.2.3.4"
#define CONFIG_HTTP_PORT 1
#define CONFIG_HTTP_THREADS 2
#define CONFIG_HTTP_REQUEST_TIMEOUT 3
#define CONFIG_HTTP_CONTENT_TIMEOUT 4

#define CONFIG_VIDEOSTREAM_CAMERA "/dev/video0"
#define CONFIG_VIDEOSTREAM_WIDTH 320
#define CONFIG_VIDEOSTREAM_HEIGHT 240
#define CONFIG_VIDEOSTREAM_SATURATION 1
#define CONFIG_VIDEOSTREAM_BRIGHTNESS 2
#define CONFIG_VIDEOSTREAM_CONTRAST 3
#define CONFIG_VIDEOSTREAM_HUE 4
#define CONFIG_VIDEOSTREAM_GAIN 5
#define CONFIG_VIDEOSTREAM_EXPOSURE 6

GTEST_TEST(config_config, from_json_1)
{
	mote::Config config;

	Json::Value json;
	json["http"]["address"] = CONFIG_HTTP_ADDRESS;
	json["http"]["port"] = CONFIG_HTTP_PORT;
	json["http"]["threads"] = CONFIG_HTTP_THREADS;
	json["http"]["request_timeout"] = CONFIG_HTTP_REQUEST_TIMEOUT;
	json["http"]["content_timeout"] = CONFIG_HTTP_CONTENT_TIMEOUT;

	json["videoStreams"]["camera"] = CONFIG_VIDEOSTREAM_CAMERA;
	json["videoStreams"]["width"] = CONFIG_VIDEOSTREAM_WIDTH;
	json["videoStreams"]["height"] = CONFIG_VIDEOSTREAM_HEIGHT;
	json["videoStreams"]["saturation"] = CONFIG_VIDEOSTREAM_SATURATION;
	json["videoStreams"]["brightness"] = CONFIG_VIDEOSTREAM_BRIGHTNESS;
	json["videoStreams"]["contrast"] = CONFIG_VIDEOSTREAM_CONTRAST;
	json["videoStreams"]["hue"] = CONFIG_VIDEOSTREAM_HUE;
	json["videoStreams"]["gain"] = CONFIG_VIDEOSTREAM_GAIN;
	json["videoStreams"]["exposure"] = CONFIG_VIDEOSTREAM_EXPOSURE;

	config.fromJson(json);
	ASSERT_EQ(CONFIG_HTTP_ADDRESS, config.http().address);
	ASSERT_EQ(CONFIG_HTTP_PORT, config.http().port);
	ASSERT_EQ(CONFIG_HTTP_THREADS, config.http().threads);
	ASSERT_EQ(CONFIG_HTTP_REQUEST_TIMEOUT, config.http().requestTimeout);
	ASSERT_EQ(CONFIG_HTTP_CONTENT_TIMEOUT, config.http().contentTimeout);

	ASSERT_EQ(1, config.videoStreams().size());
	ASSERT_EQ(CONFIG_VIDEOSTREAM_CAMERA, config.videoStreams()[0]->camera);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_WIDTH, config.videoStreams()[0]->width);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_HEIGHT, config.videoStreams()[0]->height);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_SATURATION, config.videoStreams()[0]->saturation);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_BRIGHTNESS, config.videoStreams()[0]->brightness);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_CONTRAST, config.videoStreams()[0]->contrast);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_HUE, config.videoStreams()[0]->hue);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_GAIN, config.videoStreams()[0]->gain);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_EXPOSURE, config.videoStreams()[0]->exposure);
}

GTEST_TEST(config_config, from_json_multiple_video_streams)
{
	mote::Config config;

	Json::Value json, jsonVideoStream;

	json["http"]["address"] = CONFIG_HTTP_ADDRESS;
	json["http"]["port"] = CONFIG_HTTP_PORT;
	json["http"]["threads"] = CONFIG_HTTP_THREADS;
	json["http"]["request_timeout"] = CONFIG_HTTP_REQUEST_TIMEOUT;
	json["http"]["content_timeout"] = CONFIG_HTTP_CONTENT_TIMEOUT;

	json["videoStreams"] = Json::arrayValue;
	jsonVideoStream["camera"] = CONFIG_VIDEOSTREAM_CAMERA;
	jsonVideoStream["width"] = CONFIG_VIDEOSTREAM_WIDTH;
	jsonVideoStream["height"] = CONFIG_VIDEOSTREAM_HEIGHT;
	jsonVideoStream["saturation"] = CONFIG_VIDEOSTREAM_SATURATION;
	jsonVideoStream["brightness"] = CONFIG_VIDEOSTREAM_BRIGHTNESS;
	jsonVideoStream["contrast"] = CONFIG_VIDEOSTREAM_CONTRAST;
	jsonVideoStream["hue"] = CONFIG_VIDEOSTREAM_HUE;
	jsonVideoStream["gain"] = CONFIG_VIDEOSTREAM_GAIN;
	jsonVideoStream["exposure"] = CONFIG_VIDEOSTREAM_EXPOSURE;
	json["videoStreams"].append(jsonVideoStream);

	config.fromJson(json);
	ASSERT_EQ(CONFIG_HTTP_ADDRESS, config.http().address);
	ASSERT_EQ(CONFIG_HTTP_PORT, config.http().port);
	ASSERT_EQ(CONFIG_HTTP_THREADS, config.http().threads);
	ASSERT_EQ(CONFIG_HTTP_REQUEST_TIMEOUT, config.http().requestTimeout);
	ASSERT_EQ(CONFIG_HTTP_CONTENT_TIMEOUT, config.http().contentTimeout);

	ASSERT_EQ(1, config.videoStreams().size());
	ASSERT_EQ(CONFIG_VIDEOSTREAM_CAMERA, config.videoStreams()[0]->camera);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_WIDTH, config.videoStreams()[0]->width);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_HEIGHT, config.videoStreams()[0]->height);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_SATURATION, config.videoStreams()[0]->saturation);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_BRIGHTNESS, config.videoStreams()[0]->brightness);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_CONTRAST, config.videoStreams()[0]->contrast);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_HUE, config.videoStreams()[0]->hue);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_GAIN, config.videoStreams()[0]->gain);
	ASSERT_EQ(CONFIG_VIDEOSTREAM_EXPOSURE, config.videoStreams()[0]->exposure);
}

GTEST_TEST(config_config, to_json)
{
	mote::Config config;
	{
		Json::Value json;
		json["http"]["address"] = CONFIG_HTTP_ADDRESS;
		json["http"]["port"] = CONFIG_HTTP_PORT;
		json["http"]["threads"] = CONFIG_HTTP_THREADS;
		json["http"]["request_timeout"] = CONFIG_HTTP_REQUEST_TIMEOUT;
		json["http"]["content_timeout"] = CONFIG_HTTP_CONTENT_TIMEOUT;

		json["videoStreams"]["camera"] = CONFIG_VIDEOSTREAM_CAMERA;
		json["videoStreams"]["width"] = CONFIG_VIDEOSTREAM_WIDTH;
		json["videoStreams"]["height"] = CONFIG_VIDEOSTREAM_HEIGHT;
		json["videoStreams"]["saturation"] = CONFIG_VIDEOSTREAM_SATURATION;
		json["videoStreams"]["brightness"] = CONFIG_VIDEOSTREAM_BRIGHTNESS;
		json["videoStreams"]["contrast"] = CONFIG_VIDEOSTREAM_CONTRAST;
		json["videoStreams"]["hue"] = CONFIG_VIDEOSTREAM_HUE;
		json["videoStreams"]["gain"] = CONFIG_VIDEOSTREAM_GAIN;
		json["videoStreams"]["exposure"] = CONFIG_VIDEOSTREAM_EXPOSURE;
		config.fromJson(json);
	}

	Json::Value json;
	config.toJson(json);
	ASSERT_EQ(CONFIG_HTTP_ADDRESS, json["http"]["address"].asString());
	ASSERT_EQ(CONFIG_HTTP_PORT, json["http"]["port"].asUInt());
	ASSERT_EQ(CONFIG_HTTP_THREADS, json["http"]["threads"].asUInt());
	ASSERT_EQ(CONFIG_HTTP_REQUEST_TIMEOUT, json["http"]["request_timeout"].asUInt());
	ASSERT_EQ(CONFIG_HTTP_CONTENT_TIMEOUT, json["http"]["content_timeout"].asUInt());

	ASSERT_TRUE(json["videoStreams"].isArray());
	ASSERT_EQ(1, json["videoStreams"].size());
	ASSERT_EQ(CONFIG_VIDEOSTREAM_CAMERA, json["videoStreams"][0]["camera"].asString());
	ASSERT_EQ(CONFIG_VIDEOSTREAM_WIDTH, json["videoStreams"][0]["width"].asInt());
	ASSERT_EQ(CONFIG_VIDEOSTREAM_HEIGHT, json["videoStreams"][0]["height"].asInt());
	ASSERT_EQ(CONFIG_VIDEOSTREAM_SATURATION, json["videoStreams"][0]["saturation"].asInt());
	ASSERT_EQ(CONFIG_VIDEOSTREAM_BRIGHTNESS, json["videoStreams"][0]["brightness"].asInt());
	ASSERT_EQ(CONFIG_VIDEOSTREAM_CONTRAST, json["videoStreams"][0]["contrast"].asInt());
	ASSERT_EQ(CONFIG_VIDEOSTREAM_HUE, json["videoStreams"][0]["hue"].asInt());
	ASSERT_EQ(CONFIG_VIDEOSTREAM_GAIN, json["videoStreams"][0]["gain"].asInt());
	ASSERT_EQ(CONFIG_VIDEOSTREAM_EXPOSURE, json["videoStreams"][0]["exposure"].asInt());
}
