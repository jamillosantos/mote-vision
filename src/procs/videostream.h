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

	void startTrampolin();
public:
	VideoStream(capture::devices::Camera &camera);

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
