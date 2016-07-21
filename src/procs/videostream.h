/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#ifndef MOTE_VISION_PROCS_VIDEOSTREAM_HPP
#define MOTE_VISION_PROCS_VIDEOSTREAM_HPP

#include <capture/devices/camera.h>
#include <boost/log/trivial.hpp>
#include <mutex>
#include <thread>
#include <config/videostream.h>

namespace mote
{
namespace procs
{
class VideoStreamGuard;

class VideoStream
{
	friend class VideoStreamGuard;
private:
	volatile bool _running;

	const config::VideoStream& _config;

	std::unique_ptr<capture::devices::Camera> _camera;

	std::mutex _captureMutex;

	std::unique_ptr<std::thread> _thread;

	cv::Mat _imageFrame;

	void startTrampolin();
public:
	VideoStream(const config::VideoStream &config);
	virtual ~VideoStream();

	virtual cv::Mat& frame();

	void start();

	void stop();
};

class VideoStreamGuard
{
private:
	VideoStream &_videoStream;
public:
	VideoStreamGuard(VideoStream& videoStream);

	~VideoStreamGuard();
};
}
}

#endif //MOTE_VISION_PROCS_VIDEOSTREAM_HPP
