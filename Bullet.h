/*
 * bullet.h
 *
 *  Created on: 21 џэт. 2021 у.
 *      Author: vanya
 */

#ifndef BULLET_H_
#define BULLET_H_

//#include "Dot.h"
#include "LTexGlobal.h"
#include "global.h"
class Dot;
class Enemy;
class Bullet
{
    public:
		static const int BULLET_WIDTH = 20;
		static const int BULLET_HEIGHT = 20;

		static const int BULLET_VEL = 8;

		Bullet();

		void handleEvent( SDL_Event &e, Dot &dot );

		void move(Dot &dot);

		void hittingTheEnemy(Enemy &enemy);

		void render();

		int getMPosX();
		int getMPosY();

    private:
		int mPosX, mPosY;

		int mVelX, mVelY;
};



#endif /* BULLET_H_ */
