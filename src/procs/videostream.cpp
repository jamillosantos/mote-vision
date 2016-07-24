/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 14, 2016
 */
#include <capture/exceptions.h>
#include "videostream.h"

void mote::procs::VideoStream::startTrampolin()
{
	BOOST_LOG_TRIVIAL(trace) << "Starting VideoStream at " << this->_config.camera;
	while (this->_running)
	{
		BOOST_LOG_TRIVIAL(trace) << "VideoStream::startTrampolim() - Locking";
		std::lock_guard<std::mutex> lockGuard(this->_captureMutex);
		this->_camera->read(this->_imageFrame);
		BOOST_LOG_TRIVIAL(trace) << "VideoStream::startTrampolim() - Notifying";
		this->_conditionVariable.notify_all();
		BOOST_LOG_TRIVIAL(trace) << "VideoStream::startTrampolim() - Ok";
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

void mote::procs::VideoStream::waitFrame()
{
	std::unique_lock<std::mutex> lock(this->_captureMutex);
	this->_conditionVariable.wait(lock);
}

cv::Mat &mote::procs::VideoStream::frame()
{
	return this->_imageFrame;
}

void mote::procs::VideoStream::start()
{
	this->_running = true;
	this->_camera.reset(new capture::devices::Camera());

	if (this->_config.width)
		this->_camera->width(*this->_config.width);
	if (this->_config.height)
		this->_camera->height(*this->_config.height);

	if (this->_config.saturation)
		this->_camera->saturation(*this->_config.saturation);
	if (this->_config.brightness)
		this->_camera->brightness(*this->_config.brightness);
	if (this->_config.contrast)
		this->_camera->contrast(*this->_config.contrast);
	if (this->_config.hue)
		this->_camera->hue(*this->_config.hue);
	if (this->_config.gain)
		this->_camera->gain(*this->_config.gain);
	if (this->_config.exposure)
		this->_camera->exposure(*this->_config.exposure);

	if (this->_camera->open(this->_config.camera))
		this->_thread.reset(new std::thread(&VideoStream::startTrampolin, this));
	else
	{
		this->_running = false;
		throw mote::capture::CannotOpenDevice(this->_config.camera);
	}
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