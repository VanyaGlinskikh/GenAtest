/*
 * VisionAllySensor.cc
 *
 *  Created on: 28 апр. 2021 г.
 *      Author: vanya
 */
#include "Dot.h"
#include "Enemy.h"
#include "VisionAllySensor.h"


int VisionAllySensor::location(std::vector<std::shared_ptr<Enemy>> enemy, Enemy &enemy2)
{
	for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
		if (enemy2.getId() != enemy[i]->getId())
		{
			centerEnemyPosX = enemy2.getMPosX()+(enemy2.DOT_WIDTH/2);
			centerEnemyPosY = enemy2.getMPosY()+(enemy2.DOT_HEIGHT/2);
			visionEnemyPosX = centerEnemyPosX - VISION_WIDTH/2;
			visionEnemyPosY = centerEnemyPosY - VISION_HEIGHT/2;
			if ((enemy[i]->getMPosX() < visionEnemyPosX + VISION_WIDTH && enemy[i]->getMPosY()+enemy[i]->DOT_HEIGHT > visionEnemyPosY) && (enemy[i]->getMPosX()+ enemy[i]->DOT_WIDTH > visionEnemyPosX && enemy[i]->getMPosY()+enemy[i]->DOT_HEIGHT > visionEnemyPosY) && (enemy[i]->getMPosX()+ enemy[i]->DOT_WIDTH > visionEnemyPosX && enemy[i]->getMPosY() < visionEnemyPosY+VISION_HEIGHT) && (enemy[i]->getMPosX() < visionEnemyPosX + VISION_WIDTH  && enemy[i]->getMPosY() < visionEnemyPosY+VISION_HEIGHT) )
			{
		//		std::cout<<"игрок находится в поле видимости"<<std::endl;
				return enemy[i]->getMPosX();
			}
		}
	}

//	int pole = -100;

	return -100;

}



