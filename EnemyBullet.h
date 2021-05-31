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
class Bullet;
class EnemyBullet
{
    public:
		EnemyBullet();
		EnemyBullet(const EnemyBullet&) = delete;
//		void move(Enemy &enemy);
		void move(int x, int y);
		void hittingTheAlly(Enemy &enemy);
		void hittingTheBullet(Bullet &bullet);


		static const int BULLET_WIDTH = 20;
		static const int BULLET = 20;
		static const int BULLET_VEL = 10;
		void render();

		int getMPosX();
		int getMPosY();

		void setVelY(int v){mVelY = v;};
		void setPosY(int v){mPosY = v;};
		void setPosX(int v){mPosX = v;};

    private:
		int mPosX, mPosY;
		int mVelX, mVelY;
};



#endif /* BULLET_H_ */
