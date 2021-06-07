/*
 * VisionSensor.cc
 *
 *  Created on: 29 ÿíâ. 2021 ã.
 *      Author: vanya
 */

#include "Dot.h"
#include "Enemy.h"
#include "VisionEnemySensorRight.h"

//VisionSensor::VisionSensor()
//{
//
//}

int VisionEnemySensorRight::location(Enemy &enemy, Dot &dot)
{
	centerEnemyPosX = enemy.getMPosX()+(enemy.DOT_WIDTH/2);
	centerEnemyPosY = enemy.getMPosY()+(enemy.DOT_HEIGHT/2);
	kX = dot.getMPosX()+(dot.DOT_WIDTH/2);;
	kY = dot.getMPosY()+(dot.DOT_HEIGHT/2);
	bX = centerEnemyPosX + 150;
	bY = centerEnemyPosY + 200;
	cX = centerEnemyPosX - 10;
	cY = centerEnemyPosY + 200;
	pAB = ((bX-centerEnemyPosX))*(kY-centerEnemyPosY)-(bY-centerEnemyPosY)*(kX-centerEnemyPosX);
	pBC = (cX-bX)*(kY-bY)-(cY-bY)*(kX-bX);
	pCA = (centerEnemyPosX-cX)*(kY-cY)-(centerEnemyPosY-cY)*(kX-cX);
	if (pAB > 0 && pBC > 0 && pCA > 0)
		return 1;
//			std::cout<<"ÂÍÓÒĞÈ ÒĞÅÓÃÎËÜÍÈÊÀ  "<<std::endl;

	return -100;

}


