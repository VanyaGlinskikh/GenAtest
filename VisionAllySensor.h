/*
 * VisionAllySensor.h
 *
 *  Created on: 28 апр. 2021 г.
 *      Author: vanya
 */

#ifndef VISIONALLYSENSOR_H_
#define VISIONALLYSENSOR_H_

#include "Sensor.h"
#include "vector"
#include <memory>

class Enemy;
class Dot;
class VisionAllySensor: public Sensor
{
public:

	VisionAllySensor() : Sensor(){}

	virtual ~VisionAllySensor(){};

	int location(std::vector<std::shared_ptr<Enemy>> enemy, Enemy &enemy2);
};



#endif /* VISIONALLYSENSOR_H_ */
