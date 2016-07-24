/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 22, 2016
 */

#include "videostream.h"

mote::http::actions::VideoStream::VideoStream(std::vector<std::unique_ptr<mote::procs::VideoStream>> &streams)
	: _streams(streams)
{ }
