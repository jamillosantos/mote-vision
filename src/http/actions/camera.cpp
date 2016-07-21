/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 21, 2016
 */

#include "camera.h"

mote::http::actions::CameraSnapshot::CameraSnapshot(std::vector<std::unique_ptr<mote::procs::VideoStream>>& streams)
	: _streams(streams)
{ }

void mote::http::actions::CameraSnapshot::action(mote::http::Response &response,
	SimpleWeb::Server<SimpleWeb::HTTP>::Request &request)
{
	BOOST_LOG_TRIVIAL(trace) << "CameraSnapshot::action()";
	int videoStreamIndex = -1;
	std::string ext = request.path_match[2];
	try
	{
		videoStreamIndex = boost::lexical_cast<int>(request.path_match[1]);
	}
	catch (std::exception &e)
	{
		response.status(mote::http::Status::BAD_REQUEST);
		Json::Value json;
		json["error"] = true;
		json["message"] = e.what();
		response << json;
	}
	if (videoStreamIndex < this->_streams.size())
	{
		std::vector<uchar> image;
		std::vector<int> params;
		cv::imencode("." + ext, this->_streams[videoStreamIndex]->frame(), image, params);
		response.contentType("image/" + ext);
		unsigned long size = image.size();
		response.header("Content-Length", size);
		response.write(reinterpret_cast<const char*>(image.data()), size);
	}
	else
	{
		response.status(mote::http::Status::BAD_REQUEST);
		Json::Value json;
		json["error"] = true;
		json["message"] = "Camera index is out of range.";
		response << json;
	}
}