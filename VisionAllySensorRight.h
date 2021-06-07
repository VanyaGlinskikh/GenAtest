/*
 * visionSensor.h
 *
 *  Created on: 29 ���. 2021 �.
 *      Author: vanya
 */

#ifndef VISIONALLYSENSORRIGHT_H_
#define VISIONALLYSENSORRIGHT_H_

#include "Sensor.h"

class Enemy;
class Dot;
class VisionAllySensorRight: public Sensor
{
public:

	VisionAllySensorRight() : Sensor(){}

	virtual ~VisionAllySensorRight(){};

	int location(Enemy &enemy2, std::vector<std::shared_ptr<Enemy>> enemy, std::vector<int> &enemyIdOnTheField);
};



#endif /* VISIONENEMYSENSOR_H_ */
