/*
 * CheckTeammatesSensor.cc
 *
 *  Created on: 2 ����. 2021 �.
 *      Author: vanya
 */

#include "CheckTeammatesSensor.h"
#include "Enemy.h"

void CheckTeammatesSensor::checkT(Enemy *enemy[])
{
	if (enemy[0]->getMPosX() +enemy[0]->DOT_WIDTH > enemy[1]->getMPosX() && enemy[0]->getMPosX() < enemy[1]->getMPosX()+ enemy[1]->DOT_WIDTH )
		std::cout<<" ��������� 0 ��������� ��� �����������  1"<<std::endl;
//	for (int i = 0; i < 4; ++i) {
//		for (int j = 0; j < 4; ++j) {
//			if (enemy[i]->getMPosX()+ enemy[i]->DOT_WIDTH > enemy[j]->getMPosX() && enemy[i]->getMPosX() < enemy[j]->getMPosX()+ enemy[j]->DOT_WIDTH  ){
//				std::cout<<" ��������� "<<i<<" ��������� ��� ����������� "<<j<<std::endl;
//			}
//		}
//	}

}


