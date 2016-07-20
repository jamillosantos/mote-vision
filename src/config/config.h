/**
 * @author J. Santos <jamillo@gmail.com>
 * @date July 20, 2016
 */

#ifndef MOTE_VISION_CONFIG_H
#define MOTE_VISION_CONFIG_H

#include "http.h"

namespace mote
{
class Config
	: public config::Part
{
private:
	config::Http _http;
public:
	const config::Http &http() const;

	virtual void toJson(Json::Value &json) override;

	virtual void fromJson(const Json::Value &json) override;
};
}


#endif //MOTE_VISION_CONFIG_H
