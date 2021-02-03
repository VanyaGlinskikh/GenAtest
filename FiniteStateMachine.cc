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

void FiniteStateMachine::funk(std::vector<std::shared_ptr<Sensor>> sensors, Enemy &enemy, Bullet &bullet, Dot &dot, Enemy enemy2[])
{
//	std::cout<<"проверка работы 0 "<<sensors[0]<<std::endl;
//	std::cout<<"проверка работы 1 "<<sensors[1]<<std::endl;
	if (auto ves = std::dynamic_pointer_cast<VisionEnemySensor>(sensors[0])) {
		ves->location(enemy, dot);
	}
	if (auto vdbs = std::dynamic_pointer_cast<VisionDotBulletSensor>(sensors[1])) {
		vdbs->location(enemy, bullet);
	}
	if (auto cts = std::dynamic_pointer_cast<CheckTeammatesSensor>(sensors[2])) {
		cts->checkT(&enemy2);
	}
	if (auto as = std::dynamic_pointer_cast<Azimuth>(sensors[3])) {
		as->checkA(enemy, dot);
	}
}


