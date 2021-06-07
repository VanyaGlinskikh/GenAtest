/*
 * visionSensor.h
 *
 *  Created on: 29 янв. 2021 г.
 *      Author: vanya
 */

#ifndef VISIONALLYSENSORLEFT_H_
#define VISIONALLYSENSORLEFT_H_

#include "Sensor.h"
#include <memory>

class Enemy;
class Dot;
class VisionAllySensorLeft: public Sensor
{
public:

	VisionAllySensorLeft() : Sensor(){}

	virtual ~VisionAllySensorLeft(){};

	int location(Enemy &enemy2, std::vector<std::shared_ptr<Enemy>> enemy, std::vector<int> &enemyIdOnTheField);
};



#endif /* VISIONENEMYSENSOR_H_ */
