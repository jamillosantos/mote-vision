/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 21, 2016
 */

#include "camera.h"

mote::http::actions::CameraSnapshot::CameraSnapshot(std::vector<std::unique_ptr<mote::procs::VideoStream>> &streams)
	: VideoStream(streams)
{}

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

mote::http::actions::CameraStream::CameraStream(std::vector<std::unique_ptr<mote::procs::VideoStream>> &streams)
	: VideoStream(streams)
{}

void mote::http::actions::CameraStream::action(mote::http::Response &response,
	SimpleWeb::Server<SimpleWeb::HTTP>::Request &request)
{ }

void
mote::http::actions::CameraStream::trampolin(std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response,
	std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request)
{
	mote::http::Response r(*response);
	r.status(mote::http::Status::BAD_REQUEST);
	Json::Value json;
	json["error"] = true;
	json["message"] = "This method is not supported yet.";
	r << json;
	return;
	/*
	BOOST_LOG_TRIVIAL(trace) << "CameraStream::action()";
	int videoStreamIndex = -1;
	std::string ext = request->path_match[2];
	try
	{
		videoStreamIndex = boost::lexical_cast<int>(request->path_match[1]);
	}
	catch (std::exception &e)
	{
		mote::http::Response r(*response);
		r.status(mote::http::Status::BAD_REQUEST);
		Json::Value json;
		json["error"] = true;
		json["message"] = e.what();
		r << json;
		return;
	}
	BOOST_LOG_TRIVIAL(trace) << "Starting streaming ...";
	*response << "HTTP/1.1 200 Document follows\r\n"
		"Content-Type: multipart/x-mixed-replace;boundary=" CAMERASTREAM_BOUNDARY "\r\n"
		"Connection: keep-alive\r\n\r\n";

	std::vector<uchar> image;
	std::vector<int> params;
	unsigned long size;
	while (true)							// The SimpleWeb will end this automatically when the connection gone.
	{
		BOOST_LOG_TRIVIAL(trace) << "Serving frame";
		this->_streams[videoStreamIndex]->waitFrame();
		BOOST_LOG_TRIVIAL(trace) << "Serving frame";
		cv::imencode("." + ext, this->_streams[videoStreamIndex]->frame(), image, params);
		size = image.size();
		*response << "--" CAMERASTREAM_BOUNDARY "\r\n";
		*response << "Content-Type: image/" + ext + "\r\n";
		*response << "Content-Length: " << size << "\r\n\r\n";
		response->write(reinterpret_cast<const char*>(image.data()), size);
		BOOST_LOG_TRIVIAL(trace) << "--" CAMERASTREAM_BOUNDARY;
		BOOST_LOG_TRIVIAL(trace) << "Content-Type: image/" + ext;
		BOOST_LOG_TRIVIAL(trace) << "Content-Length: " << size;
		response->write(reinterpret_cast<const char*>(image.data()), size);
		response->flush();
		// TODO: Adjust according to the server load. Maybe implement a producer/consumer. The producer
		// would care about the server loading.
		// TODO: Check if the connection still valid
		usleep(100);
	}
	 */
}
