/*
 * CheckTeammatesSensor.h
 *
 *  Created on: 2 ����. 2021 �.
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
