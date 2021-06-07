/*
 * WallGorizontalSensor.cc
 *
 *  Created on: 11 апр. 2021 г.
 *      Author: vanya
 */

#include "WallGorizontalSensor.h"

#include "Enemy.h"


int WallGorizontalSensor::location(std::shared_ptr<Enemy> enemy)
{
	return enemy->getMPosY();
}





