/*
 * VisionAllySensor.h
 *
 *  Created on: 28 апр. 2021 г.
 *      Author: vanya
 */

#ifndef VISIONALLYBULLETSENSOR_H_
#define VISIONALLYBULLETSENSOR_H_

#include "Sensor.h"
#include "vector"
#include <memory>

class EnemyBullet;
class Enemy;
class VisionAllyBulletSensor: public Sensor
{
public:

	VisionAllyBulletSensor() : Sensor(){}

	virtual ~VisionAllyBulletSensor(){};

	int location(std::vector<EnemyBullet> &enemyBullet, Enemy &enemy2);
};



#endif /* VISIONALLYSENSOR_H_ */
