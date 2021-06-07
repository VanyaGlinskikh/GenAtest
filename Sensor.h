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
		visionDotPosX=0;
		visionDotPosY=0;
		kX = 0;
		kY = 0;
		bX = 0;
		bY = 0;
		cX = 0;
		cY = 0;
		pAB = 0;
		pBC = 0;
		pCA = 0;
	}
	virtual ~Sensor(){};

	static const int VISION_WIDTH = 200;
	static const int VISION_HEIGHT = 200;

	int centerDotPosX, centerDotPosY;
	int centerEnemyPosX, centerEnemyPosY;
	int visionEnemyPosX, visionEnemyPosY;
	int visionDotPosX, visionDotPosY;
	int kX,kY, bX,bY, cX, cY;
	int pAB, pBC, pCA;


};



#endif /* SENSOR_H_ */
