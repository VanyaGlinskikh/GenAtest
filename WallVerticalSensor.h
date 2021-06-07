/*
 * WellRightSensor.h
 *
 *  Created on: 9 апр. 2021 г.
 *      Author: vanya
 */

#ifndef WALLVERTICALSENSOR_H_
#define WALLVERTICALSENSOR_H_

#include "Sensor.h"
#include "global.h"
#include <memory>

class Enemy;
class WallVerticalSensor: public Sensor
{
public:

	WallVerticalSensor() : Sensor(){}

	virtual ~WallVerticalSensor(){};

	int location(std::shared_ptr<Enemy> enemy);
};



#endif /* WALLVERTICALSENSOR_H_ */
