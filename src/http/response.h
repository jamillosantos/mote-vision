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
	static Status CONTINUE;
	static Status SWITCHING_PROTOCOLS;
	static Status PROCESSING;
	static Status OK;
	static Status CREATED;
	static Status ACCEPTED;
	static Status NON_AUTHORITATIVE_INFORMATION;
	static Status NO_CONTENT;
	static Status RESET_CONTENT;
	static Status PARTIAL_CONTENT;
	static Status MULTI_STATUS;
	static Status ALREADY_REPORTED;
	static Status IM_USED;
	static Status MULTIPLE_CHOICES;
	static Status MOVED_PERMANENTLY;
	static Status FOUND;
	static Status SEE_OTHER;
	static Status NOT_MODIFIED;
	static Status USE_PROXY;
	static Status TEMPORARY_REDIRECT;
	static Status PERMANENT_REDIRECT;
	static Status BAD_REQUEST;
	static Status UNAUTHORIZED;
	static Status PAYMENT_REQUIRED;
	static Status FORBIDDEN;
	static Status NOT_FOUND;
	static Status METHOD_NOT_ALLOWED;
	static Status NOT_ACCEPTABLE;
	static Status PROXY_AUTHENTICATION_REQUIRED;
	static Status REQUEST_TIMEOUT;
	static Status CONFLICT;
	static Status GONE;
	static Status LENGTH_REQUIRED;
	static Status PRECONDITION_FAILED;
	static Status PAYLOAD_TOO_LARGE;
	static Status REQUEST_URI_TOO_LONG;
	static Status UNSUPPORTED_MEDIA_TYPE;
	static Status REQUESTED_RANGE_NOT_SATISFIABLE;
	static Status EXPECTATION_FAILED;
	static Status IM_A_TEAPOT;
	static Status MISDIRECTED_REQUEST;
	static Status UNPROCESSABLE_ENTITY;
	static Status LOCKED;
	static Status FAILED_DEPENDENCY;
	static Status UPGRADE_REQUIRED;
	static Status PRECONDITION_REQUIRED;
	static Status TOO_MANY_REQUESTS;
	static Status REQUEST_HEADER_FIELDS_TOO_LARGE;
	static Status CONNECTION_CLOSED_WITHOUT_RESPONSE;
	static Status UNAVAILABLE_FOR_LEGAL_REASONS;
	static Status CLIENT_CLOSED_REQUEST;
	static Status INTERNAL_SERVER_ERROR;
	static Status NOT_IMPLEMENTED;
	static Status BAD_GATEWAY;
	static Status SERVICE_UNAVAILABLE;
	static Status GATEWAY_TIMEOUT;
	static Status HTTP_VERSION_NOT_SUPPORTED;
	static Status VARIANT_ALSO_NEGOTIATES;
	static Status INSUFFICIENT_STORAGE;
	static Status LOOP_DETECTED;
	static Status NOT_EXTENDED;
	static Status NETWORK_AUTHENTICATION_REQUIRED;
	static Status NETWORK_CONNECT_TIMEOUT_ERROR;

	int value;
	std::string text;

	Status(int value, const std::string &text);

	Status(const Status &status);

	Status & operator=(const Status &status);
};


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
		: _response(response), status(mote::http::Status::OK)
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
	Response& header(const std::string &header, const std::string &value)
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
	Response & header_append(const std::string &header, const std::string &value)
	{
		this->_header.insert(std::make_pair(header, value));
		return *this;
	}
};

}
}

#endif //MOTE_VISION_HTTP_RESPONSE_HPP
