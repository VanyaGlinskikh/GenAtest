/*
 * azimuth.h
 *
 *  Created on: 2 февр. 2021 г.
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

	double checkA(Enemy &enemy, Dot &dot);
};




#endif /* AZIMUTH_H_ */
