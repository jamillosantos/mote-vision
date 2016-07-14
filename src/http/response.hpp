/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 12, 2016
 */

#ifndef MOTE_VISION_HTTP_RESPONSE_HPP
#define MOTE_VISION_HTTP_RESPONSE_HPP

#include <server_https.hpp>

namespace mote
{
namespace http
{

class Status
{
public:
	int value;
	std::string text;

	Status(int value, const std::string &text)
		: value(value), text(text)
	{ }

	Status(const Status &status)
		: Status(status.value, status.text)
	{ }

	Status &operator=(const Status &status)
	{
		this->value = status.value;
		this->text = status.text;
		return *this;
	}
};


Status CONTINUE(100, "Continue");
Status SWITCHING_PROTOCOLS(101, "Switching Protocols");
Status PROCESSING(102, "Processing");
Status OK(200, "OK");
Status CREATED(201, "Created");
Status ACCEPTED(202, "Accepted");
Status NON_AUTHORITATIVE_INFORMATION(203, "Non-authoritative Information");
Status NO_CONTENT(204, "No Content");
Status RESET_CONTENT(205, "Reset Content");
Status PARTIAL_CONTENT(206, "Partial Content");
Status MULTI_STATUS(207, "Multi-Status");
Status ALREADY_REPORTED(208, "Already Reported");
Status IM_USED(226, "IM Used");
Status MULTIPLE_CHOICES(300, "Multiple Choices");
Status MOVED_PERMANENTLY(301, "Moved Permanently");
Status FOUND(302, "Found");
Status SEE_OTHER(303, "See Other");
Status NOT_MODIFIED(304, "Not Modified");
Status USE_PROXY(305, "Use Proxy");
Status TEMPORARY_REDIRECT(307, "Temporary Redirect");
Status PERMANENT_REDIRECT(308, "Permanent Redirect");
Status BAD_REQUEST(400, "Bad Request");
Status UNAUTHORIZED(401, "Unauthorized");
Status PAYMENT_REQUIRED(402, "Payment Required");
Status FORBIDDEN(403, "Forbidden");
Status NOT_FOUND(404, "Not Found");
Status METHOD_NOT_ALLOWED(405, "Method Not Allowed");
Status NOT_ACCEPTABLE(406, "Not Acceptable");
Status PROXY_AUTHENTICATION_REQUIRED(407, "Proxy Authentication Required");
Status REQUEST_TIMEOUT(408, "Request Timeout");
Status CONFLICT(409, "Conflict");
Status GONE(410, "Gone");
Status LENGTH_REQUIRED(411, "Length Required");
Status PRECONDITION_FAILED(412, "Precondition Failed");
Status PAYLOAD_TOO_LARGE(413, "Payload Too Large");
Status REQUEST_URI_TOO_LONG(414, "Request-URI Too Long");
Status UNSUPPORTED_MEDIA_TYPE(415, "Unsupported Media Type");
Status REQUESTED_RANGE_NOT_SATISFIABLE(416, "Requested Range Not Satisfiable");
Status EXPECTATION_FAILED(417, "Expectation Failed");
Status IM_A_TEAPOT(418, "I'm a teapot");
Status MISDIRECTED_REQUEST(421, "Misdirected Request");
Status UNPROCESSABLE_ENTITY(422, "Unprocessable Entity");
Status LOCKED(423, "Locked");
Status FAILED_DEPENDENCY(424, "Failed Dependency");
Status UPGRADE_REQUIRED(426, "Upgrade Required");
Status PRECONDITION_REQUIRED(428, "Precondition Required");
Status TOO_MANY_REQUESTS(429, "Too Many Requests");
Status REQUEST_HEADER_FIELDS_TOO_LARGE(431, "Request Header Fields Too Large");
Status CONNECTION_CLOSED_WITHOUT_RESPONSE(444, "Connection Closed Without Response");
Status UNAVAILABLE_FOR_LEGAL_REASONS(451, "Unavailable For Legal Reasons");
Status CLIENT_CLOSED_REQUEST(499, "Client Closed Request");
Status INTERNAL_SERVER_ERROR(500, "Internal Server Error");
Status NOT_IMPLEMENTED(501, "Not Implemented");
Status BAD_GATEWAY(502, "Bad Gateway");
Status SERVICE_UNAVAILABLE(503, "Service Unavailable");
Status GATEWAY_TIMEOUT(504, "Gateway Timeout");
Status HTTP_VERSION_NOT_SUPPORTED(505, "HTTP Version Not Supported");
Status VARIANT_ALSO_NEGOTIATES(506, "Variant Also Negotiates");
Status INSUFFICIENT_STORAGE(507, "Insufficient Storage");
Status LOOP_DETECTED(508, "Loop Detected");
Status NOT_EXTENDED(510, "Not Extended");
Status NETWORK_AUTHENTICATION_REQUIRED(511, "Network Authentication Required");
Status NETWORK_CONNECT_TIMEOUT_ERROR(599, "Network Connect Timeout Error");

template<typename T>
class Response
{
private:
	/**
	 * Based on Simple-Web-Server implementation.
	 */
	class iequal_to
	{
	public:
		bool operator()(const std::string &key1, const std::string &key2) const
		{
			return boost::algorithm::iequals(key1, key2);
		}
	};

	/**
	 * Based on Simple-Web-Server implementation.
	 */
	class ihash
	{
	public:
		size_t operator()(const std::string &key) const
		{
			std::size_t seed = 0;
			for (auto &c: key)
				boost::hash_combine(seed, std::tolower(c));
			return seed;
		}
	};

	typedef std::ostream _Response;
	typedef std::unordered_multimap<const std::string, std::string, ihash, iequal_to> _Header;

	_Response &_response;

	_Header _header;
public:
	Response(_Response &response)
		: _response(response), status(mote::http::OK)
	{ }

	Status status;

	/**
	 * Gets a header value.
	 *
	 * @param header Header name.
	 * @return Returns the header value. If not defined returns an empty string.
	 */
	std::string header(const std::string &header)
	{
		auto it = this->_header.find(header);
		if (it == this->_header.cend())
			return "";
		else
			return it->second;
	}

	/**
	 * Sets the value of the a header. If the header exists, replace the value, if does not it appends it.
	 *
	 * @param header Header name.
	 * @param value Header value to be set.
	 * @return Return the Response instance itself. For a chain call.
	 */
	Response &header(const std::string &header, const std::string &value)
	{
		auto it = this->_header.find(header);
		if (it == this->_header.cend())
			this->_header.insert(std::make_pair(header, value));
		else
			it->second = value;
		return *this;
	}

	/**
	 * Adds the header value to the end of the list.
	 *
	 * If multiple definitions of headers are needed you must use this method.
	 *
	 * @param header Header name.
	 * @param value Header value
	 * @return Return the Response instance itself. For a chain call.
	 */
	Response &header_append(const std::string &header, const std::string &value)
	{
		this->_header.insert(std::make_pair(header, value));
		return *this;
	}
};

}
}

#endif //MOTE_VISION_HTTP_RESPONSE_HPP
