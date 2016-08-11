/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#include "action.h"

void mote::http::Action::trampolin(std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response,
	std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request)
{
	mote::http::Response r(*response);
	try
	{
		this->action(r, *request);
	}
	catch (mote::http::HttpError &exception)
	{
		Json::Value json;
		json["errorCode"] = exception.errorCode();
		json["message"] = exception.what();
		const boost::optional<const Status&> &status = Status::byCode(exception.errorCode());
		if (status)
			r.status(*status);
		else
			r.status(Status::INTERNAL_SERVER_ERROR);
		r << json;
	}
	catch (std::exception &exception)
	{
		Json::Value json;
		json["errorCode"] = -1;
		json["message"] = exception.what();
		r.status(Status::INTERNAL_SERVER_ERROR);
		r << json;
	}
}
