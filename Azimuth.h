/*
 * azimuth.h
 *
 *  Created on: 2 ����. 2021 �.
 *      Author: vanya
 */

#ifndef AZIMUTH_H_
#define AZIMUTH_H_

#include "Sensor.h"
#include "string"

class Enemy;
class Dot;
class Azimuth : public Sensor
{
public:
	Azimuth() : Sensor(){}

	virtual ~Azimuth(){};

	void checkA(Enemy &enemy, Dot &dot);
};




#endif /* AZIMUTH_H_ */
