/*
 * SensorForPlayer.cc
 *
 *  Created on: 2 ���. 2021 �.
 *      Author: vanya
 */
#include "Dot.h"
#include "Enemy.h"
#include "SensorForPlayer.h"

//VisionSensor::VisionSensor()
//{
//
//}

int SensorForPlayer::location(Enemy &enemy, int x, int y)
{
	centerDotPosX = x+10;
	centerDotPosY = y+10;
	visionDotPosX = centerDotPosX - VISION_WIDTH/2;
	visionDotPosY = centerDotPosY - VISION_HEIGHT/2;
//	int pole = -100;
	if ((enemy.getMPosX() < visionDotPosX + VISION_WIDTH && enemy.getMPosY()+enemy.DOT_HEIGHT > visionDotPosY) && (enemy.getMPosX()+ enemy.DOT_WIDTH > visionDotPosX && enemy.getMPosY()+enemy.DOT_HEIGHT > visionDotPosY) && (enemy.getMPosX()+ enemy.DOT_WIDTH > visionDotPosX && enemy.getMPosY() < visionDotPosY+VISION_HEIGHT) && (enemy.getMPosX() < visionDotPosX + VISION_WIDTH  && enemy.getMPosY() < visionDotPosY+VISION_HEIGHT) )
	{
//		std::cout<<"����� ��������� � ���� ���������"<<std::endl;

		return enemy.getMPosX();
	}
	return -100;

}






