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

	void funk(std::vector<std::shared_ptr<Sensor>> sensors, Enemy &enemy, Bullet &bullet, Dot &dot, Enemy enemy2[]);
};



#endif /* FINITESTATEMACHINE_H_ */
