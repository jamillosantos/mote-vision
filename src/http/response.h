/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 12, 2016
 */

#ifndef MOTE_VISION_HTTP_RESPONSE_HPP
#define MOTE_VISION_HTTP_RESPONSE_HPP

#define HTTP_HEADER_CONTENT_TYPE "Content-Type"
#define ENDH "\r\n"

#include <server_https.hpp>
#include "exceptions.h"

namespace mote
{
namespace http
{

/**
 * Represents the status of the HTTP response.
 *
 * On the HTTP response we need to define the status of the response. Ex: 200 Ok, 404 Not Found, 500 Internal Server
 * Error, etc.
 *
 * This class keeps both the integer code and the description text required on the HTTP protocol.
 *
 * Usually, you will not need to manually define the code and text of this class. You probably is going to use the
 * built-in static declarations defined inside of the this class. Ex: `mote::http::Status::OK`,
 * `mote::http::Status::NOT_FOUND`, `mote::http::Status::INTERNAL_SERVER_ERROR`, etc.
 *
 * Source of the codes and texts: https://httpstatuses.com/
 */
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

	/**
	 * Integer code of the status.
	 */
	int value;

	/**
	 * Text description of the status.
	 */
	std::string text;

	Status(int value, const std::string &text);

	Status(const Status &status);

	Status & operator=(const Status &status);

	std::string str()
	{
		return std::to_string(this->value) + " " + this->text;
	}
};

template<typename T>
class Response
{
private:
	/**
	 * Based on Simple-Web-Server implementation. It is used on the `std::unordered_multimap` declaration.
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
	 * Based on Simple-Web-Server implementation.  It is used on the `std::unordered_multimap` declaration.
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

	std::stringstream out;

	Status _status;

	bool _flushed;

	bool _auto_flush;

	void ensureNotFlushed()
	{
		if (this->_flushed)
			throw already_been_flushed();
	}
public:
	Response(_Response &response)
		: _response(response), _status(mote::http::Status::OK), _flushed(false), _auto_flush(false)
	{ }

	~Response()
	{
		if (!this->_auto_flush)
		{
			if (!this->_flushed)
			{
				size_t len = this->out.tellp();
				this->header("Content-Length", len);
			}
			this->flush();
		}
	}

	/**
	 * Status' property getter.
	 *
	 * The status of an HTTP request keeps the response code and text of the response itself. Ex: 200 Ok, 404 Not found.
	 *
	 * For using the status you should use the static definitions at `mote::http::Status::*`.
	 *
	 * @see mote::http::Status
	 */
	const Status &status()
	{
		return this->_status;
	}

	/**
	 * Status' property setter.
	 *
	 * @see status()
	 */
	Response& status(const Status& status)
	{
		this->_status = status;
		return *this;
	}

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
		this->ensureNotFlushed();
		auto it = this->_header.find(header);
		if (it != this->_header.cend())
			this->_header.erase(it);
		this->_header.insert(std::make_pair(header, value));
		return *this;
	}

	/**
	 * Any type implementation for header. It uses the `std::to_string` implementention, hence it is restricted to its
	 * types implementations.
	 *
	 * @see header(std::string, std::string)
	 */
	Response& header(const std::string &header, size_t &value)
	{
		return this->header(header, std::to_string(value));
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
		this->ensureNotFlushed();
		this->_header.insert(std::make_pair(header, value));
		return *this;
	}

	/**
	 * Content-type header getter.
	 *
	 * It is an alias for `header("Content-Type")`.
	 *
	 * @return Returns the `Content-type` header value.
	 */
	std::string contentType()
	{
		return this->header(HTTP_HEADER_CONTENT_TYPE);
	}

	/**
	 * Content-type header setter.
	 *
	 * It is an alias for `header("Content-Type", value)`.
	 *
	 * @param value Value of th `Content-Type` header
	 * @return Returns the own class instance
	 */
	Response& contentType(const std::string &value)
	{
		return this->header(HTTP_HEADER_CONTENT_TYPE, value);
	}

	/**
	 * Operator implementation to enables iostream writing style.
	 */
	template <typename C>
	Response& operator<<(const C& _)
	{
		if (this->_auto_flush)
		{
			if (!this->_flushed)
				this->flush();
			this->_response << _;
		}
		else
			this->out << _;
	}

	/**
	 * Flushes the response.
	 */
	void flush()
	{
		if (this->_flushed)
			this->_response << this->out.rdbuf();
		else
		{
			this->_response << "HTTP/1.1 " << this->_status.value << " " << this->_status.text << ENDH;
			for (const std::pair<std::string, std::string>& h : this->_header)
			{
				this->_response << h.first << " " << h.second << ENDH;
			}
			this->_response << ENDH;
			this->_response << this->out.rdbuf();
			this->_flushed = true;
		}
	}
};

}
}

#endif //MOTE_VISION_HTTP_RESPONSE_HPP
