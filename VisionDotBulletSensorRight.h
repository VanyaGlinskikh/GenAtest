/*
 * visionSensor.h
 *
 *  Created on: 29 ���. 2021 �.
 *      Author: vanya
 */

#ifndef VISIONDOTBULLETSENSORRIGHT_H_
#define VISIONDOTBULLETSENSORRIGHT_H_

#include "Sensor.h"

class Enemy;
class Bullet;
class VisionDotBulletSensorRight: public Sensor
{
public:

	VisionDotBulletSensorRight() : Sensor(){}

	virtual ~VisionDotBulletSensorRight(){};

	int location(Enemy &enemy, Bullet &bullet);
};



#endif /* VISIONENEMYSENSOR_H_ */
