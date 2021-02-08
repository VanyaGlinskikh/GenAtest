/*
 * azimuth.cc
 *
 *  Created on: 2 ����. 2021 �.
 *      Author: vanya
 */

#include "Azimuth.h"
#include "Enemy.h"
#include "Dot.h"
#include <math.h>
#include <sstream>
double Azimuth::checkA(Enemy &enemy, Dot &dot)
{	centerDotPosY = dot.getMPosY()+(dot.DOT_HEIGHT/2);
	centerEnemyPosX = enemy.getMPosX()+(enemy.DOT_WIDTH/2);

	centerEnemyPosY = enemy.getMPosY()+(enemy.DOT_HEIGHT/2);
	centerDotPosX = dot.getMPosX()+(dot.DOT_WIDTH/2);
	int posX = enemy.getMPosX()+(enemy.DOT_WIDTH/2);
	int posY = dot.getMPosY()+(dot.DOT_HEIGHT/2);
	int vecBC = posX - centerDotPosX;
	int vecAC = posY - centerEnemyPosY;
//	std::cout<<"atan2 ����� "<<atan2(vecBC, vecAC)* (180/acos(-1.0))<<", ���������� �� ���������� �� ������ "<<hypot(vecBC, vecAC)<<std::endl;
	return atan2(vecBC, vecAC)* (180/acos(-1.0));
}


