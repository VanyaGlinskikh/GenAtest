/*
 * visionSensor.h
 *
 *  Created on: 29 џэт. 2021 у.
 *      Author: vanya
 */

#ifndef VISIONENEMYSENSOR_H_
#define VISIONENEMYSENSOR_H_

#include "Sensor.h"

class Enemy;
class Dot;
class VisionEnemySensor: public Sensor
{
public:
	static const int VISION_WIDTH = 120;
	static const int VISION_HEIGHT = 120;

	VisionEnemySensor() : Sensor(){
		centerEnemyPosX =0;
		centerEnemyPosY=0;
		visionEnemyPosX=0;
		visionEnemyPosY=0;
	}

	void location(Enemy &enemy, Dot &dot);
private:
	int centerEnemyPosX;
	int centerEnemyPosY;
	int visionEnemyPosX;
	int visionEnemyPosY;
};



#endif /* VISIONENEMYSENSOR_H_ */
