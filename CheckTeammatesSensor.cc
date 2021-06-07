/*
 * CheckTeammatesSensor.cc
 *
 *  Created on: 2 февр. 2021 г.
 *      Author: vanya
 */

#include "CheckTeammatesSensor.h"
#include "Enemy.h"

int CheckTeammatesSensor::checkT(std::vector<Enemy> &enemy)
{
//	if (enemy[0].getMPosX() +enemy[0].DOT_WIDTH > enemy[1].getMPosX() && enemy[0].getMPosX() < enemy[1].getMPosX()+ enemy[1].DOT_WIDTH )
//		std::cout<<" противник 0 находится над противником  1"<<std::endl;
	for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
		for (int j = 0; j < NUMBEROFOPPONENTS; ++j) {
			if (enemy[i].getMPosX()+ enemy[i].DOT_WIDTH > enemy[j].getMPosX() && enemy[i].getMPosX() < enemy[j].getMPosX()+ enemy[j].DOT_WIDTH  ){
//				std::cout<<" противник "<<i<<" находится над противником "<<j<<std::endl;
			}
		}
	}
	return 1;

}


