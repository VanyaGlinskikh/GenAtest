/*
 * SensorForPlayer.h
 *
 *  Created on: 2 июн. 2021 г.
 *      Author: vanya
 */

#ifndef SENSORFORPLAYER_H_
#define SENSORFORPLAYER_H_

#include "Sensor.h"

class Enemy;
class Dot;
class SensorForPlayer: public Sensor
{
public:

	SensorForPlayer() : Sensor(){}

	virtual ~SensorForPlayer(){};

	int location(Enemy &enemy, int x, int y);
};



#endif /* SENSORFORPLAYER_H_ */
