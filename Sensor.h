/*
 * Sensor.h
 *
 *  Created on: 29 џэт. 2021 у.
 *      Author: vanya
 */

#ifndef SENSOR_H_
#define SENSOR_H_

class Sensor
{
public:
	Sensor(){
		centerEnemyPosX =0;
		centerEnemyPosY=0;
		visionEnemyPosX=0;
		visionEnemyPosY=0;
	}

	static const int VISION_WIDTH = 120;
	static const int VISION_HEIGHT = 120;

	int centerEnemyPosX;
	int centerEnemyPosY;
	int visionEnemyPosX;
	int visionEnemyPosY;


};



#endif /* SENSOR_H_ */
