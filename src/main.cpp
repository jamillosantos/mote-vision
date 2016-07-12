/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#include <http/server.hpp>
#include "application.hpp"

#include <boost/log/trivial.hpp>

using namespace mote;

Application app;

void handleInt(int sig)
{
	BOOST_LOG_TRIVIAL(trace) << "Interruption received";
	app.stop();
}

int main()
{
	signal(SIGINT, handleInt);
	return app.run();
}