/*
 * visionSensor.h
 *
 *  Created on: 29 янв. 2021 г.
 *      Author: vanya
 */

#ifndef VISIONDOTBULLETSENSORLEFT_H_
#define VISIONDOTBULLETSENSORLEFT_H_

#include "Sensor.h"

class Enemy;
class Bullet;
class VisionDotBulletSensorLeft: public Sensor
{
public:

	VisionDotBulletSensorLeft() : Sensor(){}

	virtual ~VisionDotBulletSensorLeft(){};

	int location(Enemy &enemy, Bullet &bullet);
};



#endif /* VISIONENEMYSENSOR_H_ */
