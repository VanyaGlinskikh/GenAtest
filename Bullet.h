/*
 * bullet.h
 *
 *  Created on: 21 янв. 2021 г.
 *      Author: vanya
 */

#ifndef BULLET_H_
#define BULLET_H_

//#include "Dot.h"
#include "global.h"
#include "LTexture.h"
class Dot;
class Enemy;
class EnemyBullet;
class Bullet
{
    public:
		static const int BULLET_WIDTH = 20;
		static const int BULLET_HEIGHT = 20;

		static const int BULLET_VEL = 10;

		Bullet();

		void handleEvent( SDL_Event &e, Dot &dot );

		void move(Dot &dot);

		void hittingTheEnemy(Enemy &enemy);
		void hittingTheEnemyBullet(EnemyBullet &enemybullet);

		void render();

		int getMPosX();
		int getMPosY();
		void setPosY(int v){mPosY = v;};
		void setPosX(int v){mPosX = v;};
		void setVelY(int v){mVelY = v;};

    private:
		int mPosX, mPosY;

		int mVelX, mVelY;
};



#endif /* BULLET_H_ */
