/*
 * VisionSensor.cc
 *
 *  Created on: 29 янв. 2021 г.
 *      Author: vanya
 */

#include "Bullet.h"
#include "Enemy.h"
#include "VisionDotBulletSensorRight.h"

//VisionSensor::VisionSensor()
//{
//
//}

int VisionDotBulletSensorRight::location(Enemy &enemy, Bullet &bullet)
{
	centerEnemyPosX = enemy.position().x + Enemy::WIDTH / 2;
	centerEnemyPosY = enemy.position().y + Enemy::HEIGHT / 2;
	kX = bullet.position().x + Bullet::WIDTH / 2;
	kY = bullet.position().y + Bullet::HEIGHT / 2;
	// FIXME: что это за магические числа?
	bX = centerEnemyPosX + 150;
	bY = centerEnemyPosY + 200;
	cX = centerEnemyPosX - 10;
	cY = centerEnemyPosY + 200;
	pAB = ((bX-centerEnemyPosX))*(kY-centerEnemyPosY)-(bY-centerEnemyPosY)*(kX-centerEnemyPosX);
	pBC = (cX-bX)*(kY-bY)-(cY-bY)*(kX-bX);
	pCA = (centerEnemyPosX-cX)*(kY-cY)-(centerEnemyPosY-cY)*(kX-cX);
	if (pAB > 0 && pBC > 0 && pCA > 0)
		return 1;
//			std::cout<<"ВНУТРИ ТРЕУГОЛЬНИКА  "<<std::endl;

	return -100;

}


