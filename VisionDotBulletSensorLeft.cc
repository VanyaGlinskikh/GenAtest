/*
 * VisionSensor.cc
 *
 *  Created on: 29 янв. 2021 г.
 *      Author: vanya
 */

#include "Bullet.h"
#include "Enemy.h"
#include "VisionDotBulletSensorLeft.h"

//VisionSensor::VisionSensor()
//{
//
//}

int VisionDotBulletSensorLeft::location(Enemy &enemy, Bullet &bullet)
{
	centerEnemyPosX = enemy.getMPosX()+(enemy.DOT_WIDTH/2);
	centerEnemyPosY = enemy.getMPosY()+(enemy.DOT_HEIGHT/2);
	kX = bullet.getMPosX()+(bullet.BULLET_WIDTH/2);;
	kY = bullet.getMPosY()+(bullet.BULLET_HEIGHT/2);
	bX = centerEnemyPosX - 150;
	bY = centerEnemyPosY + 200;
	cX = centerEnemyPosX + 10;
	cY = centerEnemyPosY + 200;
	pAB = (bX-centerEnemyPosX)*(kY-centerEnemyPosY)-(bY-centerEnemyPosY)*(kX-centerEnemyPosX);
	pBC = (cX-bX)*(kY-bY)-(cY-bY)*(kX-bX);
	pCA = (centerEnemyPosX-cX)*(kY-cY)-(centerEnemyPosY-cY)*(kX-cX);

		if (pAB < 0 && pBC < 0 && pCA < 0)
			std::cout<<"ВНУТРИ ТРЕУГОЛЬНИКА  "<<std::endl;

		return -100;



}


