/*
 * CheckTeammatesSensor.h
 *
 *  Created on: 2 февр. 2021 г.
 *      Author: vanya
 */

#ifndef CHECKTEAMMATESSENSOR_H_
#define CHECKTEAMMATESSENSOR_H_

#include "Sensor.h"
#include "vector"

class Enemy;
class CheckTeammatesSensor : public Sensor
{
public:
	CheckTeammatesSensor() : Sensor(){}

	virtual ~CheckTeammatesSensor(){};

	int checkT(std::vector<Enemy> &enemy);
};

#endif /* CHECKTEAMMATESSENSOR_H_ */
