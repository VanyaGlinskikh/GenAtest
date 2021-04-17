/*
 * WallRightSensor.cc
 *
 *  Created on: 9 апр. 2021 г.
 *      Author: vanya
 */

#include "WallVerticalSensor.h"

#include "Enemy.h"


int WallVerticalSensor::location(std::shared_ptr<Enemy> enemy)
{
	return enemy->getMPosX();
}


