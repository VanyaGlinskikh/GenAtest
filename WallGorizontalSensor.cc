/*
 * WallGorizontalSensor.cc
 *
 *  Created on: 11 ���. 2021 �.
 *      Author: vanya
 */

#include "WallGorizontalSensor.h"

#include "Enemy.h"


int WallGorizontalSensor::location(std::shared_ptr<Enemy> enemy)
{
	return enemy->getMPosY();
}





