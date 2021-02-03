/*
 * VisionDotBulletSensor.cc
 *
 *  Created on: 30 янв. 2021 г.
 *      Author: vanya
 */
#include "Bullet.h"
#include "Enemy.h"
#include "VisionDotBulletSensor.h"

void VisionDotBulletSensor::location(Enemy &enemy, Bullet &bullet)
{
	centerEnemyPosX = enemy.getMPosX()+(enemy.DOT_WIDTH/2);
	centerEnemyPosY = enemy.getMPosY()+(enemy.DOT_HEIGHT/2);
	visionEnemyPosX = centerEnemyPosX - VISION_WIDTH/2;
	visionEnemyPosY = centerEnemyPosY - VISION_HEIGHT/2;

	if ((bullet.getMPosX() < visionEnemyPosX + VISION_WIDTH && bullet.getMPosY()+bullet.BULLET_HEIGHT > visionEnemyPosY) && (bullet.getMPosX()+ bullet.BULLET_WIDTH > visionEnemyPosX && bullet.getMPosY()+bullet.BULLET_HEIGHT > visionEnemyPosY) && (bullet.getMPosX()+ bullet.BULLET_WIDTH > visionEnemyPosX && bullet.getMPosY() < visionEnemyPosY+VISION_HEIGHT) && (bullet.getMPosX() < visionEnemyPosX + VISION_WIDTH  && bullet.getMPosY() < visionEnemyPosY+VISION_HEIGHT) )
	{
//		std::cout<<"пуля находится в поле видимости"<<std::endl;
	}

}



