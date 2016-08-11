/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 14, 2016
 */

#include "response.h"

std::map<int, mote::http::Status*> mote::http::Status::_statuses;

mote::http::Status mote::http::Status::CONTINUE(100, "Continue");
mote::http::Status mote::http::Status::SWITCHING_PROTOCOLS(101, "Switching Protocols");
mote::http::Status mote::http::Status::PROCESSING(102, "Processing");
mote::http::Status mote::http::Status::OK(200, "OK");
mote::http::Status mote::http::Status::CREATED(201, "Created");
mote::http::Status mote::http::Status::ACCEPTED(202, "Accepted");
mote::http::Status mote::http::Status::NON_AUTHORITATIVE_INFORMATION(203, "Non-authoritative Information");
mote::http::Status mote::http::Status::NO_CONTENT(204, "No Content");
mote::http::Status mote::http::Status::RESET_CONTENT(205, "Reset Content");
mote::http::Status mote::http::Status::PARTIAL_CONTENT(206, "Partial Content");
mote::http::Status mote::http::Status::MULTI_STATUS(207, "Multi-Status");
mote::http::Status mote::http::Status::ALREADY_REPORTED(208, "Already Reported");
mote::http::Status mote::http::Status::IM_USED(226, "IM Used");
mote::http::Status mote::http::Status::MULTIPLE_CHOICES(300, "Multiple Choices");
mote::http::Status mote::http::Status::MOVED_PERMANENTLY(301, "Moved Permanently");
mote::http::Status mote::http::Status::FOUND(302, "Found");
mote::http::Status mote::http::Status::SEE_OTHER(303, "See Other");
mote::http::Status mote::http::Status::NOT_MODIFIED(304, "Not Modified");
mote::http::Status mote::http::Status::USE_PROXY(305, "Use Proxy");
mote::http::Status mote::http::Status::TEMPORARY_REDIRECT(307, "Temporary Redirect");
mote::http::Status mote::http::Status::PERMANENT_REDIRECT(308, "Permanent Redirect");
mote::http::Status mote::http::Status::BAD_REQUEST(400, "Bad Request");
mote::http::Status mote::http::Status::UNAUTHORIZED(401, "Unauthorized");
mote::http::Status mote::http::Status::PAYMENT_REQUIRED(402, "Payment Required");
mote::http::Status mote::http::Status::FORBIDDEN(403, "Forbidden");
mote::http::Status mote::http::Status::NOT_FOUND(404, "Not Found");
mote::http::Status mote::http::Status::METHOD_NOT_ALLOWED(405, "Method Not Allowed");
mote::http::Status mote::http::Status::NOT_ACCEPTABLE(406, "Not Acceptable");
mote::http::Status mote::http::Status::PROXY_AUTHENTICATION_REQUIRED(407, "Proxy Authentication Required");
mote::http::Status mote::http::Status::REQUEST_TIMEOUT(408, "Request Timeout");
mote::http::Status mote::http::Status::CONFLICT(409, "Conflict");
mote::http::Status mote::http::Status::GONE(410, "Gone");
mote::http::Status mote::http::Status::LENGTH_REQUIRED(411, "Length Required");
mote::http::Status mote::http::Status::PRECONDITION_FAILED(412, "Precondition Failed");
mote::http::Status mote::http::Status::PAYLOAD_TOO_LARGE(413, "Payload Too Large");
mote::http::Status mote::http::Status::REQUEST_URI_TOO_LONG(414, "Request-URI Too Long");
mote::http::Status mote::http::Status::UNSUPPORTED_MEDIA_TYPE(415, "Unsupported Media Type");
mote::http::Status mote::http::Status::REQUESTED_RANGE_NOT_SATISFIABLE(416, "Requested Range Not Satisfiable");
mote::http::Status mote::http::Status::EXPECTATION_FAILED(417, "Expectation Failed");
mote::http::Status mote::http::Status::IM_A_TEAPOT(418, "I'm a teapot");
mote::http::Status mote::http::Status::MISDIRECTED_REQUEST(421, "Misdirected Request");
mote::http::Status mote::http::Status::UNPROCESSABLE_ENTITY(422, "Unprocessable Entity");
mote::http::Status mote::http::Status::LOCKED(423, "Locked");
mote::http::Status mote::http::Status::FAILED_DEPENDENCY(424, "Failed Dependency");
mote::http::Status mote::http::Status::UPGRADE_REQUIRED(426, "Upgrade Required");
mote::http::Status mote::http::Status::PRECONDITION_REQUIRED(428, "Precondition Required");
mote::http::Status mote::http::Status::TOO_MANY_REQUESTS(429, "Too Many Requests");
mote::http::Status mote::http::Status::REQUEST_HEADER_FIELDS_TOO_LARGE(431, "Request Header Fields Too Large");
mote::http::Status mote::http::Status::CONNECTION_CLOSED_WITHOUT_RESPONSE(444, "Connection Closed Without Response");
mote::http::Status mote::http::Status::UNAVAILABLE_FOR_LEGAL_REASONS(451, "Unavailable For Legal Reasons");
mote::http::Status mote::http::Status::CLIENT_CLOSED_REQUEST(499, "Client Closed Request");
mote::http::Status mote::http::Status::INTERNAL_SERVER_ERROR(500, "Internal Server Error");
mote::http::Status mote::http::Status::NOT_IMPLEMENTED(501, "Not Implemented");
mote::http::Status mote::http::Status::BAD_GATEWAY(502, "Bad Gateway");
mote::http::Status mote::http::Status::SERVICE_UNAVAILABLE(503, "Service Unavailable");
mote::http::Status mote::http::Status::GATEWAY_TIMEOUT(504, "Gateway Timeout");
mote::http::Status mote::http::Status::HTTP_VERSION_NOT_SUPPORTED(505, "HTTP Version Not Supported");
mote::http::Status mote::http::Status::VARIANT_ALSO_NEGOTIATES(506, "Variant Also Negotiates");
mote::http::Status mote::http::Status::INSUFFICIENT_STORAGE(507, "Insufficient Storage");
mote::http::Status mote::http::Status::LOOP_DETECTED(508, "Loop Detected");
mote::http::Status mote::http::Status::NOT_EXTENDED(510, "Not Extended");
mote::http::Status mote::http::Status::NETWORK_AUTHENTICATION_REQUIRED(511, "Network Authentication Required");
mote::http::Status mote::http::Status::NETWORK_CONNECT_TIMEOUT_ERROR(599, "Network Connect Timeout Error");

boost::optional<const mote::http::Status&> mote::http::Status::byCode(int code)
{
	if (_statuses.find(code) == _statuses.end())
		return boost::optional<const mote::http::Status&>();
	else
		return *_statuses[code];
}

mote::http::Status::Status(int value, const std::string &text) : value(value), text(text)
{
	if (_statuses.find(value) == _statuses.end())
		_statuses[value] = this;
}

mote::http::Status::Status(const Status &status) : Status(status.value, status.text)
{ }

mote::http::Status &mote::http::Status::operator=(const Status &status)
{
	this->value = status.value;
	this->text = status.text;
	return *this;
}
