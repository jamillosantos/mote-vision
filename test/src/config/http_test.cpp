/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#include <gtest/gtest.h>
#include <config/http.h>

#define CONFIG_HTTP_ADDRESS "1.2.3.4"
#define CONFIG_HTTP_PORT 1
#define CONFIG_HTTP_THREADS 2
#define CONFIG_HTTP_REQUEST_TIMEOUT 3
#define CONFIG_HTTP_CONTENT_TIMEOUT 4

GTEST_TEST(config_http, constructor_params)
{
	::mote::config::Http config(CONFIG_HTTP_ADDRESS, CONFIG_HTTP_PORT, CONFIG_HTTP_THREADS, CONFIG_HTTP_REQUEST_TIMEOUT,
		CONFIG_HTTP_CONTENT_TIMEOUT);
	ASSERT_EQ(CONFIG_HTTP_ADDRESS, config.address);
	ASSERT_EQ(CONFIG_HTTP_PORT, config.port);
	ASSERT_EQ(CONFIG_HTTP_THREADS, config.threads);
	ASSERT_EQ(CONFIG_HTTP_REQUEST_TIMEOUT, config.request_timeout);
	ASSERT_EQ(CONFIG_HTTP_CONTENT_TIMEOUT, config.content_timeout);
}
