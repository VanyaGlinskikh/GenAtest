/*
 * CheckTeammatesSensor.h
 *
 *  Created on: 2 ����. 2021 �.
 *      Author: vanya
 */

#ifndef CHECKTEAMMATESSENSOR_H_
#define CHECKTEAMMATESSENSOR_H_

#include "Sensor.h"

class Enemy;
class CheckTeammatesSensor : public Sensor
{
public:
	CheckTeammatesSensor() : Sensor(){}

	virtual ~CheckTeammatesSensor(){};

	void checkT(Enemy *enemy[]);
};

#endif /* CHECKTEAMMATESSENSOR_H_ */
