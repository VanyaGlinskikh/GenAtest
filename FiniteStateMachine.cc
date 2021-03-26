/*
 * FiniteStateMachine.cc
 *
 *  Created on: 3 Ñ„ÐµÐ²Ñ€. 2021 Ð³.
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
	int ves1;
	int vdbs1;
	int cts1;
	double an1;
	if (auto ves = std::dynamic_pointer_cast<VisionEnemySensor>(sensors[0])) {
		ves1 = ves->location(enemy, dot);
	}
	if (auto vdbs = std::dynamic_pointer_cast<VisionDotBulletSensor>(sensors[1])) {
		 vdbs1 = vdbs->location(enemy, bullet);
	}

	if (auto cts = std::dynamic_pointer_cast<CheckTeammatesSensor>(sensors[2])) {
		cts1 = cts->checkT(enemy2);
	}

	if (auto as = std::dynamic_pointer_cast<Azimuth>(sensors[3])) {
		 an1 = as->checkA(enemy, dot);
	}

	std::vector<double> naborZnachSensor;
	naborZnachSensor.push_back(ves1);
	naborZnachSensor.push_back(vdbs1);
	naborZnachSensor.push_back(cts1);
	naborZnachSensor.push_back(an1);



//	if (predCheckBulletRight(vdbs1, enemy.getMPosX()))
//	{
//		enemy.moveRight();
//	}
//	if (predCheckBulletLeft(vdbs1, enemy.getMPosX()))
//	{
//		enemy.moveLeft();
//	}

//	if (predCheckAzimuthRight(an1) && predInSight(ves1))
//	{
//		enemy.moveRight();
//	}
//
//	if (predCheckAzimuthLeft(an1) && predInSight(ves1))
//	{
//		enemy.moveLeft();
//	}

}

void FiniteStateMachine::konAvt(std::vector<double> &zn, int &q, std::vector<double> &gen, int &a, Enemy &enemy)
{
	// q = 0 - ïîèñê
	gen = {3, 2, 4, 2, 5, 1, 8, 7};
	if (q == 0){
		if (predCheckBulletRight(zn[1], enemy.getMPosX() ) ){
			a = 1;
		}
		if (predCheckBulletLeft(zn[1], enemy.getMPosX() ) ){
			a = 2;
		}
		else
			a = 0;

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

bool FiniteStateMachine::predCheckAzimuthLeft(double an)
{
	if (an> 0)
		return 1;
	return 0;
}

bool FiniteStateMachine::predCheckAzimuthRight(double an)
{
	if (an < 0)
		return 1;
	return 0;
}

bool FiniteStateMachine::predInSight(int ves)
{
	if(ves != -100)
		return 1;
	return 0;
}


