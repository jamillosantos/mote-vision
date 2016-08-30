/**
 * @author J. Santos <jamillo@gmail.com>
 * @date August 30, 2016
 */

#include "resources.h"

boost::filesystem::path Resources::_basePath(TEST_RESOURCE_DIR);

Lena Resources::_lena;
SprintMarker Resources::_sprintMarker;

boost::filesystem::path Resources::path()
{
	return _basePath;
}

Lena &Resources::lena()
{
	return _lena;
}

SprintMarker &Resources::sprintMarker()
{
	return _sprintMarker;
}

const boost::filesystem::path Lena::path(const std::string &extension)
{
	return Resources::path() / (std::string("lena.") + extension);
}

boost::filesystem::path Lena::jpg()
{
	return this->path("jpg");
}

boost::filesystem::path Lena::png()
{
	return this->path("png");
}

boost::filesystem::path SprintMarker::path(const unsigned int index) const
{
	return Resources::path() / "sprint_markers" / (std::to_string(index) + std::string(".ppm"));
}
