/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 12, 2016
 */

#include <gtest/gtest.h>
#include <boost/thread.hpp>
#include <http/response.h>

#define HTTPRESPONSE_HEADER_NAME_1 "Content-Type"
#define HTTPRESPONSE_HEADER_VALUE_1 "text/html"
#define HTTPRESPONSE_HEADER_NAME_2 "User-Agent"
#define HTTPRESPONSE_HEADER_VALUE_2 "Pseudo Browser"

GTEST_TEST(HttpResponse, params)
{
	std::stringbuf sbuf;
	std::ostream originalResponse(&sbuf);
	mote::http::Response<SimpleWeb::HTTP> response(originalResponse);
	response.header(HTTPRESPONSE_HEADER_NAME_1, HTTPRESPONSE_HEADER_VALUE_1);
	response.header(HTTPRESPONSE_HEADER_NAME_2, HTTPRESPONSE_HEADER_VALUE_2);
	ASSERT_EQ(HTTPRESPONSE_HEADER_VALUE_1, response.header(HTTPRESPONSE_HEADER_NAME_1));
	ASSERT_EQ(HTTPRESPONSE_HEADER_VALUE_2, response.header(HTTPRESPONSE_HEADER_NAME_2));
}
