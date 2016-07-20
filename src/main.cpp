/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 11, 2016
 */

#include <http/server.h>
#include "application.h"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <json/reader.h>
#include <json/value.h>

using namespace mote;

Application app;

void handleInt(int sig)
{
	BOOST_LOG_TRIVIAL(trace) << "Interruption received";
	app.stop();
}


int main(int argc, char **argv)
{
	namespace po = boost::program_options;

	std::string configFile;

	po::options_description desc("Options");
	desc.add_options()
		("help,h", "displays this help message")
		("config,c", po::value<std::string>(&configFile)->default_value(DEFAULT_CONFIG_FILE), "Specifies the config file")
		("version,v", "displays the version of the system")
		;

	po::variables_map vm;
	po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout << "Usage: " << argv[0] << " [Options]" << std::endl << std::endl;
		std::cout << desc << std::endl;
		return 0;
	}
	else
	{
		BOOST_LOG_TRIVIAL(trace) << "Using config file: " << configFile;

		boost::filesystem::path pathConfigFile(configFile);
		if (boost::filesystem::exists(configFile))
		{
			signal(SIGINT, handleInt);
			Json::Reader reader;
			std::ifstream stream(configFile);
			Json::Value configJson;
			reader.parse(stream, configJson, false);
			app.config(configJson);
			return app.run();
		}
		else
		{
			BOOST_LOG_TRIVIAL(fatal) << "The config file was not found.";
			return 1;
		}
	}
}