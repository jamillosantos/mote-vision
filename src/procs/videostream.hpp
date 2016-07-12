/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#ifndef MOTE_VISION_PROCS_VIDEOSTREAM_HPP
#define MOTE_VISION_PROCS_VIDEOSTREAM_HPP

#include <capture/devices/device.hpp>
#include <mutex>
#include <thread>

namespace mote
{
namespace procs
{
class VideoStreamGuard;

class VideoStream
{
	friend class VideoStreamGuard;
private:
	capture::devices::Camera& _camera;

	std::mutex _captureMutex;

	std::unique_ptr<std::thread> _thread;

	volatile bool _running;

	cv::Mat _imageFrame;

	void startTrampolin()
	{
		while (this->_running)
		{
			std::lock_guard<std::mutex> lockGuard(this->_captureMutex);
			this->_camera.read(this->_imageFrame);
		}
	}
public:
	VideoStream(capture::devices::Camera &camera)
		: _camera(camera), _running(false)
	{ }

	void start()
	{
		this->_running = true;
		this->_thread.reset(new std::thread(&VideoStream::startTrampolin, this));
	}

	void stop()
	{
		this->_running = false;
		if (this->_thread)
		{
			BOOST_LOG_TRIVIAL(trace) << "Stopping VideoStream ...";
			this->_thread->join();
			this->_thread.release();
		}
	}
};

class VideoStreamGuard
{
private:
	VideoStream &_videoStream;
public:
	VideoStreamGuard(VideoStream& videoStream)
		: _videoStream(videoStream)
	{
		this->_videoStream._captureMutex.lock();
	}

	~VideoStreamGuard()
	{
		this->_videoStream._captureMutex.unlock();
	}
};
}
}

#endif //MOTE_VISION_PROCS_VIDEOSTREAM_HPP
