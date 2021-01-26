/*
 * bullet.h
 *
 *  Created on: 21 ���. 2021 �.
 *      Author: vanya
 */

#ifndef BULLET_H_
#define BULLET_H_

//#include "Dot.h"
class Dot;
class Bullet
{
    public:
		static const int BULLET_WIDTH = 20;
		static const int BULLET = 20;

		static const int BULLET_VEL = 10;

		Bullet();

		void handleEvent( SDL_Event& e, const Dot &dot );

		void move(const Dot &dot);

		void render();

		int getMPosX();
		int getMPosY();

    private:
		int mPosX, mPosY;

		int mVelX, mVelY;
};



#endif /* BULLET_H_ */
