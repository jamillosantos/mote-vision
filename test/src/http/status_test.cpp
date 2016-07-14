/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 14, 2016
 */

#include <gtest/gtest.h>
#include <http/response.hpp>

#define HTTP_STATUS_CODE 123
#define HTTP_STATUS_TEXT "Test Text"

GTEST_TEST(HttpStatus, constructor)
{
	mote::http::Status status(HTTP_STATUS_CODE, HTTP_STATUS_TEXT);
	ASSERT_EQ(HTTP_STATUS_CODE, status.value);
	ASSERT_EQ(HTTP_STATUS_TEXT, status.text);
}

GTEST_TEST(HttpStatus, constructor_copy)
{
	mote::http::Status status(mote::http::OK);
	ASSERT_EQ(mote::http::OK.value, status.value);
	ASSERT_EQ(mote::http::OK.text, status.text);
}

GTEST_TEST(HttpStatus, assign_operator)
{
	mote::http::Status status(mote::http::OK);
	status = mote::http::BAD_REQUEST;
	ASSERT_EQ(mote::http::BAD_REQUEST.value, status.value);
	ASSERT_EQ(mote::http::BAD_REQUEST.text, status.text);
}
