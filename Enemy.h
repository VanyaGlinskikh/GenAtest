/*
 * Enemy.h
 *
 *  Created on: 13 сент. 2020 г.
 *      Author: vanya
 */

#ifndef ENEMY_H_
#define ENEMY_H_

//#include "Bullet.h"
#include "global.h"
#include "LTexGlobal.h"

class Bullet;
class Enemy
{
    public:
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;
		static const int DOT_VEL = 10;


		Enemy();

		void move(Bullet &bullet);

		void render();

		void funk();

		int getMPosX();
		int getMPosY();

    private:
		int mPosX, mPosY;
		int mVelX, mVelY;
};




#endif /* ENEMY_H_ */
