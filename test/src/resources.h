/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 09, 2016
 */

#ifndef MOTE_VISION_RESOURCES_H
#define MOTE_VISION_RESOURCES_H

#include <boost/filesystem.hpp>

class Lena;

class SprintMarker;

class Resources
{
private:
	static boost::filesystem::path _basePath;

	static Lena _lena;

	static SprintMarker _sprintMarker;

public:
	static boost::filesystem::path path();

	static Lena& lena();

	static SprintMarker& sprintMarker();
};

class Lena
{
protected:
	const boost::filesystem::path path(const std::string& extension);

public:
	const int width = 512;

	const int height = 512;

	boost::filesystem::path jpg();

	boost::filesystem::path png();
};

class SprintMarker
{
protected:

public:
	boost::filesystem::path path(const unsigned int index) const;
};

#endif //MOTE_VISION_RESOURCES_H
