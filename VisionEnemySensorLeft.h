/*
 * visionSensor.h
 *
 *  Created on: 29 янв. 2021 г.
 *      Author: vanya
 */

#ifndef VISIONENEMYSENSORLEFT_H_
#define VISIONENEMYSENSORLEFT_H_

#include "Sensor.h"

class Enemy;
class Dot;
class VisionEnemySensorLeft: public Sensor
{
public:

	VisionEnemySensorLeft() : Sensor(){}

	virtual ~VisionEnemySensorLeft(){};

	int location(Enemy &enemy, Dot &dot);
};



#endif /* VISIONENEMYSENSOR_H_ */
