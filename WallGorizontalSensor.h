/*
 * WallGorizontalSensor.h
 *
 *  Created on: 11 апр. 2021 г.
 *      Author: vanya
 */

#ifndef WALLGORIZONTALSENSOR_H_
#define WALLGORIZONTALSENSOR_H_

#include "Sensor.h"
#include "global.h"
#include <memory>

class Enemy;
class WallGorizontalSensor: public Sensor
{
public:

	WallGorizontalSensor() : Sensor(){}

	virtual ~WallGorizontalSensor(){};

	int location(std::shared_ptr<Enemy> enemy);
};




#endif /* WALLGORIZONTALSENSOR_H_ */
