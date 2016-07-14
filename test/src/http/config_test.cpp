/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#include <gtest/gtest.h>
#include <http/config.h>

GTEST_TEST(HttpConfig, constructor_params)
{
	mote::http::Config config(1, 2, 3, 4);
	ASSERT_EQ(1, config.port);
	ASSERT_EQ(2, config.threads);
	ASSERT_EQ(3, config.request_timeout);
	ASSERT_EQ(4, config.content_timeout);
}
