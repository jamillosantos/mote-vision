/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include "http.h"

mote::config::Http::Http()
	: Http(HTTP_CONFIG_DEFAULT_ADDRESS, HTTP_CONFIG_DEFAULT_PORT, HTTP_CONFIG_DEFAULT_THREADS, HTTP_CONFIG_DEFAULT_REQUEST_TIMEOUT,
	HTTP_CONFIG_DEFAULT_CONTENT_TIMEOUT)
{ }

mote::config::Http::Http(const std::string &address, unsigned short port, unsigned short threads,
	unsigned short request_timeout, unsigned short timeout_content)
	: address(address), port(port), threads(threads), request_timeout(request_timeout), content_timeout(timeout_content)
{ }

void mote::config::Http::to_json(Json::Value &json)
{
	json["address"] = this->address;
	json["port"] = this->port;
	json["threads"] = this->threads;
	json["request_timeout"] = this->request_timeout;
	json["content_timeout"] = this->content_timeout;
}

void mote::config::Http::from_json(const Json::Value &json)
{
	this->address = json["address"].asString();
	this->port = json["port"].asUInt();
	this->threads = json["threads"].asUInt();
	this->request_timeout = json["request_timeout"].asUInt();
	this->content_timeout = json["content_timeout"].asUInt();
}