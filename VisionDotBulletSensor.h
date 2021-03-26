/*
 * VisionDotBulletSensor.h
 *
 *  Created on: 30 ���. 2021 �.
 *      Author: vanya
 */

#ifndef VISIONDOTBULLETSENSOR_H_
#define VISIONDOTBULLETSENSOR_H_

#include "Sensor.h"

class Enemy;
class Bullet;
class VisionDotBulletSensor: public Sensor
{
public:

	VisionDotBulletSensor() : Sensor(){}

	virtual ~VisionDotBulletSensor(){};

	double location(Enemy &enemy, Bullet &bullet);
};



#endif /* VISIONDOTBULLETSENSOR_H_ */
