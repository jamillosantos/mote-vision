/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 14, 2016
 */
#include "videostream.h"

void mote::procs::VideoStream::startTrampolin()
{
	while (this->_running)
	{
		std::lock_guard<std::mutex> lockGuard(this->_captureMutex);
		this->_camera->read(this->_imageFrame);
	}
}

mote::procs::VideoStream::VideoStream(const mote::config::VideoStream &config)
	: _running(false), _config(config)
{ }


mote::procs::VideoStream::~VideoStream()
{
	if (this->_running)
		this->stop();
}


void mote::procs::VideoStream::start()
{
	this->_running = true;
	this->_camera.reset(new capture::devices::Camera());
	this->_camera->open(0);
	this->_thread.reset(new std::thread(&VideoStream::startTrampolin, this));
}

void mote::procs::VideoStream::stop()
{
	this->_running = false;
	if (this->_thread)
	{
		BOOST_LOG_TRIVIAL(trace) << "Stopping VideoStream ...";
		this->_thread->join();
		this->_thread.release();
	}
}

mote::procs::VideoStreamGuard::VideoStreamGuard(VideoStream& videoStream) : _videoStream(videoStream)
{
	this->_videoStream._captureMutex.lock();
}

mote::procs::VideoStreamGuard::~VideoStreamGuard()
{
	this->_videoStream._captureMutex.unlock();
}