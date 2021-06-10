/*
 * VisionSensor.cc
 *
 *  Created on: 29 янв. 2021 г.
 *      Author: vanya
 */

#include "Enemy.h"
#include "VisionAllySensorLeft.h"

int VisionAllySensorLeft::location(Enemy &enemy2, std::vector<std::shared_ptr<Enemy>> enemy, std::vector<int> &enemyIdOnTheField)
{
	centerEnemyPosX = enemy2.position().x+(Enemy::WIDTH/2);
	centerEnemyPosY = enemy2.position().y+(Enemy::HEIGHT/2);

	for (int i = 0; i < SIMULTANEOUS_NUMBER_OF_ENEMY_ON_THE_FIELD; ++i) {
		if (enemy2.getId() != enemy[enemyIdOnTheField[i]]->getId()){
			kX = enemy[enemyIdOnTheField[i]]->position().x+(Enemy::WIDTH/2);
			kY = enemy[enemyIdOnTheField[i]]->position().x+(Enemy::HEIGHT/2);
			// FIXME: что это за магические числа?
			bX = centerEnemyPosX - 150;
			bY = centerEnemyPosY + 200;
			cX = centerEnemyPosX + 10;
			cY = centerEnemyPosY + 200;

			pAB = (bX-centerEnemyPosX)*(kY-centerEnemyPosY)-(bY-centerEnemyPosY)*(kX-centerEnemyPosX);
			pBC = (cX-bX)*(kY-bY)-(cY-bY)*(kX-bX);
			pCA = (centerEnemyPosX-cX)*(kY-cY)-(centerEnemyPosY-cY)*(kX-cX);

			if (pAB < 0 && pBC < 0 && pCA < 0)
				return 1;
//				std::cout<<"ВНУТРИ ТРЕУГОЛЬНИКА  "<<std::endl;
		}

	}

		return -100;



}


