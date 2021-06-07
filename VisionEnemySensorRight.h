/*
 * visionSensor.h
 *
 *  Created on: 29 џэт. 2021 у.
 *      Author: vanya
 */

#ifndef VISIONENEMYSENSORRIGHT_H_
#define VISIONENEMYSENSORRIGHT_H_

#include "Sensor.h"

class Enemy;
class Dot;
class VisionEnemySensorRight: public Sensor
{
public:

	VisionEnemySensorRight() : Sensor(){}

	virtual ~VisionEnemySensorRight(){};

	int location(Enemy &enemy, Dot &dot);
};



#endif /* VISIONENEMYSENSOR_H_ */
