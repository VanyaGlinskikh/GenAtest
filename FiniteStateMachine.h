/*
 * FiniteStateMachine.h
 *
 *  Created on: 3 февр. 2021 г.
 *      Author: vanya
 */

#ifndef FINITESTATEMACHINE_H_
#define FINITESTATEMACHINE_H_

#include "vector"
#include "memory"

class Sensor;
class Dot;
class Enemy;
class Bullet;
class FiniteStateMachine{

public:
	FiniteStateMachine(){};

	void funk(std::vector<std::shared_ptr<Sensor>> sensors,Enemy &enemy, Bullet &bullet, Dot &dot, std::vector<Enemy> &enemy2);

	void konAvt(std::vector<double> &zn, int &q, std::vector<double> &gen, int &a, Enemy &enemy);

	bool predCheckBulletRight(int a, int b);
	bool predCheckBulletLeft(int a, int b);
	bool predCheckAzimuthRight(double a);
	bool predCheckAzimuthLeft(double a);
	bool predInSight(int ves);
};



#endif /* FINITESTATEMACHINE_H_ */
