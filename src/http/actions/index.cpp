/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include "index.h"

void
mote::http::actions::Index::action(mote::http::Response &response, SimpleWeb::Server<SimpleWeb::HTTP>::Request &request)
{
	BOOST_LOG_TRIVIAL(trace) << "Index::action()";
	Json::Value json;
	json["message"] = "The server is up.";
	response << json;
}
