/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#ifndef MOTE_VISION_CONFIG_PART_H
#define MOTE_VISION_CONFIG_PART_H

#include <json/value.h>

namespace mote
{
namespace config
{
/**
 * This class represents a part of a configuration. Every module will have a part for itself.
 */
class Part
{
public:
	/**
	 * Method that will put this configuration into a JSON object.]
	 *
	 * @param json Object that have the properties set.
	 */
	virtual void toJson(Json::Value &json) const = 0;

	/**
	 * Loads this configuration object from a JSON object.
	 *
	 * @param json Object that will be the source of the loaded properties.
	 */
	virtual void fromJson(const Json::Value &json) = 0;
};
}
}


#endif //MOTE_VISION_CONFIG_PART_H
