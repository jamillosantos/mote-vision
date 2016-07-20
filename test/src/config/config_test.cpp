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

GTEST_TEST(config_config, from_json)
{
	mote::Config config;

	Json::Value json;
	json["http"]["address"] = CONFIG_HTTP_ADDRESS;
	json["http"]["port"] = CONFIG_HTTP_PORT;
	json["http"]["threads"] = CONFIG_HTTP_THREADS;
	json["http"]["request_timeout"] = CONFIG_HTTP_REQUEST_TIMEOUT;
	json["http"]["content_timeout"] = CONFIG_HTTP_CONTENT_TIMEOUT;

	config.fromJson(json);
	ASSERT_EQ(CONFIG_HTTP_ADDRESS, config.http().address);
	ASSERT_EQ(CONFIG_HTTP_PORT, config.http().port);
	ASSERT_EQ(CONFIG_HTTP_THREADS, config.http().threads);
	ASSERT_EQ(CONFIG_HTTP_REQUEST_TIMEOUT, config.http().requestTimeout);
	ASSERT_EQ(CONFIG_HTTP_CONTENT_TIMEOUT, config.http().contentTimeout);
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
		config.fromJson(json);
	}

	Json::Value json;
	config.toJson(json);
	ASSERT_EQ(CONFIG_HTTP_ADDRESS, json["http"]["address"].asString());
	ASSERT_EQ(CONFIG_HTTP_PORT, json["http"]["port"].asUInt());
	ASSERT_EQ(CONFIG_HTTP_THREADS, json["http"]["threads"].asUInt());
	ASSERT_EQ(CONFIG_HTTP_REQUEST_TIMEOUT, json["http"]["request_timeout"].asUInt());
	ASSERT_EQ(CONFIG_HTTP_CONTENT_TIMEOUT, json["http"]["content_timeout"].asUInt());
}
