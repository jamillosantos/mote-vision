/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 09, 2016
 */

#ifndef MOTE_VISION_RESOURCES_HPP
#define MOTE_VISION_RESOURCES_HPP

#include <boost/filesystem.hpp>

class Lena;

class Resources
{
private:
	static boost::filesystem::path basePath;

	static Lena _lena;

public:
	static boost::filesystem::path path()
	{
		return basePath;
	}

	static Lena& lena()
	{
		return _lena;
	}
};

class Lena
{
protected:
	const boost::filesystem::path path(const std::string& extension)
	{
		return Resources::path() / (std::string("lena.") + extension);
	}

public:
	const int width = 512;

	const int height = 512;

	boost::filesystem::path jpg()
	{
		return this->path("jpg");
	}

	boost::filesystem::path png()
	{
		return this->path("png");
	}
};

boost::filesystem::path Resources::basePath(TEST_RESOURCE_DIR);
Lena Resources::_lena;

#endif //MOTE_VISION_RESOURCES_HPP
