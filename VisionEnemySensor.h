/*
 * visionSensor.h
 *
 *  Created on: 29 янв. 2021 г.
 *      Author: vanya
 */

#ifndef VISIONENEMYSENSOR_H_
#define VISIONENEMYSENSOR_H_

#include "Sensor.h"

class Enemy;
class Dot;
class VisionEnemySensor: public Sensor
{
public:

	VisionEnemySensor() : Sensor(){}

	virtual ~VisionEnemySensor(){};

	int location(Enemy &enemy, Dot &dot);
};



#endif /* VISIONENEMYSENSOR_H_ */
