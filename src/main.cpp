/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#include <http/server.h>
#include "application.h"

using namespace mote;

Application app;

void handleInt(int sig)
{
	BOOST_LOG_TRIVIAL(trace) << "Interruption received";
	app.stop();
}

int main(int argc, char** argv)
{
	signal(SIGINT, handleInt);
	return app.run();
}