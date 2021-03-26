/*
 * bullet.h
 *
 *  Created on: 21 џэт. 2021 у.
 *      Author: vanya
 */

#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_

//#include "Enemy.h"
#include "LTexGlobal.h"
class Enemy;
class Genome;
class EnemyBullet
{
    public:
		EnemyBullet();
		void move(Enemy &enemy);


		static const int BULLET_WIDTH = 20;
		static const int BULLET = 20;
		static const int BULLET_VEL = 10;
		void render();

		int getMPosX();
		int getMPosY();

    private:
		int mPosX, mPosY;
		int mVelX, mVelY;
};



#endif /* BULLET_H_ */
