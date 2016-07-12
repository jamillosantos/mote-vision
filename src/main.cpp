/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#include <iostream>

#include <http/server.hpp>

using namespace mote;

int main()
{
	http::Config config;
	std::cout << "Starting http server at " << config.port << " ..." << std::endl;
	http::Server server(config);
	try
	{
		server.start();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error starting HTTP Server: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}