/*
 * azimuth.cc
 *
 *  Created on: 2 февр. 2021 г.
 *      Author: vanya
 */

#include "Azimuth.h"
#include "Enemy.h"
#include "Dot.h"
#include <math.h>
#include <sstream>

void Azimuth::checkA(Enemy &enemy, Dot &dot)
{
	centerEnemyPosX = enemy.getMPosX()+(enemy.DOT_WIDTH/2);
	centerEnemyPosY = enemy.getMPosY()+(enemy.DOT_HEIGHT/2);
	centerDotPosX = dot.getMPosX()+(dot.DOT_WIDTH/2);
	centerDotPosY = dot.getMPosY()+(dot.DOT_HEIGHT/2);
	int tPosX = enemy.getMPosX()+(enemy.DOT_WIDTH/2);
	int tPosY = dot.getMPosY()+(dot.DOT_HEIGHT/2);

	double cosAB = (tPosX*centerDotPosX + tPosY*centerDotPosY)/( sqrt( (tPosX^2)*(tPosY^2) ) * sqrt( (centerDotPosX^2)*(centerDotPosY^2) ) );
//	double arccosAB = acos(cosAB);
//	std::cout<<"косинус угла равен "<<cosAB<<", а угол равен "<<acos(cosAB)<<std::endl;
}


