/*
 * VisionSensor.cc
 *
 *  Created on: 29 янв. 2021 г.
 *      Author: vanya
 */

#include "Dot.h"
#include "Enemy.h"
#include "VisionEnemySensorLeft.h"

//VisionSensor::VisionSensor()
//{
//
//}

int VisionEnemySensorLeft::location(Enemy &enemy, Dot &dot)
{
	centerEnemyPosX = enemy.position().x + Enemy::WIDTH / 2;
	centerEnemyPosY = enemy.position().y + Enemy::HEIGHT / 2;
	kX = dot.position().x + Dot::WIDTH / 2;
	kY = dot.position().y + Dot::HEIGHT / 2;
	// FIXME: что это за магические числа?
	bX = centerEnemyPosX - 150;
	bY = centerEnemyPosY + 350;
	cX = centerEnemyPosX + 10;
	cY = centerEnemyPosY + 350;
	pAB = (bX-centerEnemyPosX)*(kY-centerEnemyPosY)-(bY-centerEnemyPosY)*(kX-centerEnemyPosX);
	pBC = (cX-bX)*(kY-bY)-(cY-bY)*(kX-bX);
	pCA = (centerEnemyPosX-cX)*(kY-cY)-(centerEnemyPosY-cY)*(kX-cX);
//	visionEnemyPosX = centerEnemyPosX - VISION_WIDTH/2;
//	visionEnemyPosY = centerEnemyPosY - VISION_HEIGHT/2;
//	int pole = -100;

//		std::cout<<"значение pAB:  "<<pAB<<std::endl;
//		std::cout<<"значение pBC:  "<<pBC<<std::endl;
//		std::cout<<"значение pCA:  "<<pCA<<std::endl;

		if (pAB < 0 && pBC < 0 && pCA < 0)
			return 1;
//			std::cout<<"ВНУТРИ ТРЕУГОЛЬНИКА  "<<std::endl;

		return -100;



}


