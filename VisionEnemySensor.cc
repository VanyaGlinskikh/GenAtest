/*
 * VisionSensor.cc
 *
 *  Created on: 29 янв. 2021 г.
 *      Author: vanya
 */

#include "Dot.h"
#include "Enemy.h"
#include "VisionEnemySensor.h"

//VisionSensor::VisionSensor()
//{
//
//}

void VisionEnemySensor::location(Enemy &enemy, Dot &dot)
{
	int centerEnemyPosX = enemy.getMPosX()+(enemy.DOT_WIDTH/2);
	int centerEnemyPosY = enemy.getMPosY()+(enemy.DOT_HEIGHT/2);
	int visionEnemyPosX = centerEnemyPosX - VISION_WIDTH/2;
	int visionEnemyPosY = centerEnemyPosY - VISION_HEIGHT/2;

	if ((dot.getMPosX() < visionEnemyPosX + VISION_WIDTH && dot.getMPosY()+dot.DOT_HEIGHT > visionEnemyPosY) && (dot.getMPosX()+ dot.DOT_WIDTH > visionEnemyPosX && dot.getMPosY()+dot.DOT_HEIGHT > visionEnemyPosY) && (dot.getMPosX()+ dot.DOT_WIDTH > visionEnemyPosX && dot.getMPosY() < visionEnemyPosY+VISION_HEIGHT) && (dot.getMPosX() < visionEnemyPosX + VISION_WIDTH  && dot.getMPosY() < visionEnemyPosY+VISION_HEIGHT) )
	{
		std::cout<<"находится в поле видимости"<<std::endl;
	}

}


