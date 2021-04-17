/*
 * WallRightSensor.cc
 *
 *  Created on: 9 ���. 2021 �.
 *      Author: vanya
 */

#include "WallVerticalSensor.h"

#include "Enemy.h"


int WallVerticalSensor::location(std::shared_ptr<Enemy> enemy)
{
	return enemy->getMPosX();
}


