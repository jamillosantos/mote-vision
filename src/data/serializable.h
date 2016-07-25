/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 24, 2016
 */

#ifndef MOTE_VISION_DATA_SERIALIZABLE_H
#define MOTE_VISION_DATA_SERIALIZABLE_H

#include <json/value.h>

namespace mote
{
namespace data
{
class Serializable
{
public:
	virtual void fromJson(const Json::Value &json) = 0;
	virtual void toJson(Json::Value &json) = 0;
};
}
}

#endif //MOTE_VISION_DATA_SERIALIZABLE_H
