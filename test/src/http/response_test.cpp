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

#define HTTPRESPONSE_CONTENT1 "<h1>Header 1</h1>"
#define HTTPRESPONSE_CONTENT2 "<p>Another content</p>"

#define HTTPRESPONSE_PACKET1 "HTTP/1.1 200 OK\r\n" \
	"Content-Length: 39\r\n" \
	"User-Agent: Pseudo Browser\r\n" \
	"Content-Type: text/html\r\n\r\n" \
	HTTPRESPONSE_CONTENT1 HTTPRESPONSE_CONTENT2

#define HTTPRESPONSE_PACKET1 "HTTP/1.1 200 OK\r\n" \
	"Content-Length: 39\r\n" \
	"User-Agent: Pseudo Browser\r\n" \
	"Content-Type: text/html\r\n\r\n" \
	HTTPRESPONSE_CONTENT1 HTTPRESPONSE_CONTENT2

#define HTTPRESPONSE_PACKET2 "HTTP/1.1 500 Internal Server Error\r\n\r\n" HTTPRESPONSE_CONTENT1 HTTPRESPONSE_CONTENT2

#define HTTPRESPONSE_CONTENT_TYPE_JSON "application/json"
#define HTTPRESPONSE_PACKET_JSON "HTTP/1.1 200 OK\r\nContent-Length: 29\r\nContent-Type: application/json\r\n\r\n{\"message\":\"This is a json.\"}"


GTEST_TEST(http_response, params)
{
	std::stringbuf sbuf;
	std::ostream originalResponse(&sbuf);
	mote::http::ResponseBase<SimpleWeb::HTTP> response(originalResponse);
	response.header(HTTPRESPONSE_HEADER_NAME_1, HTTPRESPONSE_HEADER_VALUE_1);
	response.header(HTTPRESPONSE_HEADER_NAME_2, HTTPRESPONSE_HEADER_VALUE_2);
	ASSERT_EQ(HTTPRESPONSE_HEADER_VALUE_1, response.header(HTTPRESPONSE_HEADER_NAME_1));
	ASSERT_EQ(HTTPRESPONSE_HEADER_VALUE_2, response.header(HTTPRESPONSE_HEADER_NAME_2));
}

GTEST_TEST(http_response, params_replace)
{
	std::stringbuf sbuf;
	std::ostream originalResponse(&sbuf);
	mote::http::ResponseBase<SimpleWeb::HTTP> response(originalResponse);
	response.header(HTTPRESPONSE_HEADER_NAME_1, HTTPRESPONSE_HEADER_VALUE_1);
	response.header(HTTPRESPONSE_HEADER_NAME_1, HTTPRESPONSE_HEADER_VALUE_2);
	ASSERT_EQ(HTTPRESPONSE_HEADER_VALUE_2, response.header(HTTPRESPONSE_HEADER_NAME_1));
}

GTEST_TEST(http_response, status)
{
	std::stringbuf sbuf;
	std::ostream originalResponse(&sbuf);
	mote::http::ResponseBase<SimpleWeb::HTTP> response(originalResponse);
	response.status(mote::http::Status::IM_A_TEAPOT);
	ASSERT_EQ(mote::http::Status::IM_A_TEAPOT.value, response.status().value);
	ASSERT_EQ(mote::http::Status::IM_A_TEAPOT.text, response.status().text);
}

GTEST_TEST(http_response, content_type)
{
	std::stringbuf sbuf;
	std::ostream originalResponse(&sbuf);
	mote::http::ResponseBase<SimpleWeb::HTTP> response(originalResponse);
	response.contentType(HTTPRESPONSE_HEADER_VALUE_1);
	ASSERT_EQ(HTTPRESPONSE_HEADER_VALUE_1, response.contentType());
	ASSERT_EQ(HTTPRESPONSE_HEADER_VALUE_1, response.header(HTTPRESPONSE_HEADER_NAME_1));
}

GTEST_TEST(http_response, flush_1)
{
	std::stringbuf sbuf;
	std::ostream originalResponse(&sbuf);
	{
		mote::http::ResponseBase<SimpleWeb::HTTP> response(originalResponse);
		response.status(mote::http::Status::OK);
		response.contentType(HTTPRESPONSE_HEADER_VALUE_1);
		response.header(HTTPRESPONSE_HEADER_NAME_2, HTTPRESPONSE_HEADER_VALUE_2);
		response << HTTPRESPONSE_CONTENT1;
		response << HTTPRESPONSE_CONTENT2;
	}
	std::string r = sbuf.str();
	ASSERT_EQ(HTTPRESPONSE_PACKET1, r);
}

GTEST_TEST(http_response, flush_2)
{
	std::stringbuf sbuf;
	std::ostream originalResponse(&sbuf);
	mote::http::ResponseBase<SimpleWeb::HTTP> response(originalResponse);
	response.status(mote::http::Status::INTERNAL_SERVER_ERROR);
	response << HTTPRESPONSE_CONTENT1;
	response << HTTPRESPONSE_CONTENT2;
	response.flush();
	std::string r = sbuf.str();
	ASSERT_EQ(HTTPRESPONSE_PACKET2, r);
}

GTEST_TEST(http_response, setting_header_already_flushed_error)
{
	std::stringbuf sbuf;
	std::ostream originalResponse(&sbuf);
	mote::http::ResponseBase<SimpleWeb::HTTP> response(originalResponse);
	response.status(mote::http::Status::INTERNAL_SERVER_ERROR);
	response << HTTPRESPONSE_CONTENT1;
	response.flush();
	ASSERT_THROW(response.header(HTTPRESPONSE_HEADER_NAME_1, HTTPRESPONSE_HEADER_VALUE_1), mote::http::already_been_flushed);
}

GTEST_TEST(http_response, json_success)
{
	std::stringbuf sbuf;
	std::ostream originalResponse(&sbuf);
	{
		mote::http::ResponseBase<SimpleWeb::HTTP> response(originalResponse);
		Json::Value json;
		json["message"] = "This is a json.";
		response << json;
		ASSERT_EQ(HTTPRESPONSE_CONTENT_TYPE_JSON, response.contentType());
	}
	ASSERT_EQ(HTTPRESPONSE_PACKET_JSON, sbuf.str());
}
