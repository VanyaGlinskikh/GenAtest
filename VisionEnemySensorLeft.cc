/*
 * VisionSensor.cc
 *
 *  Created on: 29 ���. 2021 �.
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
	centerEnemyPosX = enemy.getMPosX()+(enemy.DOT_WIDTH/2);
	centerEnemyPosY = enemy.getMPosY()+(enemy.DOT_HEIGHT/2);
	kX = dot.getMPosX()+(dot.DOT_WIDTH/2);;
	kY = dot.getMPosY()+(dot.DOT_HEIGHT/2);
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

//		std::cout<<"�������� pAB:  "<<pAB<<std::endl;
//		std::cout<<"�������� pBC:  "<<pBC<<std::endl;
//		std::cout<<"�������� pCA:  "<<pCA<<std::endl;

		if (pAB < 0 && pBC < 0 && pCA < 0)
			return 1;
//			std::cout<<"������ ������������  "<<std::endl;

		return -100;



}


