/*
 * Sensor.h
 *
 *  Created on: 29 џэт. 2021 у.
 *      Author: vanya
 */

#ifndef SENSOR_H_
#define SENSOR_H_

class Enemy;
class Dot;
class Sensor
{
public:
	Sensor(){
		centerEnemyPosX =0;
		centerEnemyPosY=0;
		centerDotPosX =0;
		centerDotPosY=0;
		visionEnemyPosX=0;
		visionEnemyPosY=0;
	}
	virtual ~Sensor(){};

	static const int VISION_WIDTH = 200;
	static const int VISION_HEIGHT = 200;

	int centerDotPosX;
	int centerDotPosY;
	int centerEnemyPosX;
	int centerEnemyPosY;
	int visionEnemyPosX;
	int visionEnemyPosY;


};



#endif /* SENSOR_H_ */
