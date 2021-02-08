/*
 * FiniteStateMachine.cc
 *
 *  Created on: 3 С„РµРІСЂ. 2021 Рі.
 *      Author: vanya
 */
#include "FiniteStateMachine.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Dot.h"
#include "VisionDotBulletSensor.h"
#include "VisionEnemySensor.h"
#include "CheckTeammatesSensor.h"
#include "Azimuth.h"

void FiniteStateMachine::funk(std::vector<std::shared_ptr<Sensor>> sensors, Enemy &enemy, Bullet &bullet, Dot &dot, std::vector<Enemy> &enemy2)
{
	if (auto ves = std::dynamic_pointer_cast<VisionEnemySensor>(sensors[0])) {
		ves->location(enemy, dot);
	}
	if (auto vdbs = std::dynamic_pointer_cast<VisionDotBulletSensor>(sensors[1])) {
		int a = vdbs->location(enemy, bullet);

		if (predCheckBulletRight(a, enemy.getMPosX()))
		{
//			std::cout<<"мы попали в проверку"<<std::endl;
			enemy.moveRight();
		}
		if (predCheckBulletLeft(a, enemy.getMPosX()))
		{
			std::cout<<"мы попали в проверку"<<std::endl;
			enemy.moveLeft();
		}
	}
	if (auto cts = std::dynamic_pointer_cast<CheckTeammatesSensor>(sensors[2])) {
		cts->checkT(enemy2);
	}
	if (auto as = std::dynamic_pointer_cast<Azimuth>(sensors[3])) {
		as->checkA(enemy, dot);
	}
}

bool FiniteStateMachine::predCheckBulletRight(int posXBull, int posXEnemy)
{
	if ((posXBull ==  posXEnemy || posXBull+20 > posXEnemy) && posXBull > 0 && posXBull < posXEnemy)
		return 1;
	return 0;
}

bool FiniteStateMachine::predCheckBulletLeft(int posXBull, int posXEnemy)
{
	if (posXBull < posXEnemy+20  && posXBull > 0 && posXBull > posXEnemy)
		return 1;
	return 0;
}

