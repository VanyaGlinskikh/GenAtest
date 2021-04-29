/*
 * VisionAllySensor.cc
 *
 *  Created on: 28 апр. 2021 г.
 *      Author: vanya
 */
#include "Dot.h"
#include "EnemyBullet.h"
#include "Enemy.h"
#include "VisionAllyBulletSensor.h"


int VisionAllyBulletSensor::location(std::vector<EnemyBullet> &enemyBullet, Enemy &enemy2)
{
	for (int i = 0; i < NUMBEROFENEMYBULLETS; ++i) {

		if (enemy2.getId() != i)
		{
			centerEnemyPosX = enemy2.getMPosX()+(enemy2.DOT_WIDTH/2);
			centerEnemyPosY = enemy2.getMPosY()+(enemy2.DOT_HEIGHT/2);
			visionEnemyPosX = centerEnemyPosX - VISION_WIDTH/2;
			visionEnemyPosY = centerEnemyPosY - VISION_HEIGHT/2;
			if ((enemyBullet[i].getMPosX() < visionEnemyPosX + VISION_WIDTH && enemyBullet[i].getMPosY()+enemyBullet[i].BULLET_WIDTH > visionEnemyPosY) && (enemyBullet[i].getMPosX()+ enemyBullet[i].BULLET_WIDTH > visionEnemyPosX && enemyBullet[i].getMPosY()+enemyBullet[i].BULLET_WIDTH > visionEnemyPosY) && (enemyBullet[i].getMPosX()+ enemyBullet[i].BULLET_WIDTH > visionEnemyPosX && enemyBullet[i].getMPosY() < visionEnemyPosY+VISION_HEIGHT) && (enemyBullet[i].getMPosX() < visionEnemyPosX + VISION_WIDTH  && enemyBullet[i].getMPosY() < visionEnemyPosY+VISION_HEIGHT) )
			{
		//		std::cout<<"игрок находится в поле видимости"<<std::endl;
				return enemyBullet[i].getMPosX();
			}
		}
	}

//	int pole = -100;

	return -100;

}



