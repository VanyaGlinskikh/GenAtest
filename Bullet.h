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
#include "Sprite.h"

class Dot;
class Enemy;
class EnemyBullet;

class Bullet: public Sprite
{
    public:
		static const int WIDTH = 20;
		static const int HEIGHT = 20;

		static const int VELOCITY = 10;

		Bullet();

		void handleEvent( SDL_Event &e, Dot &dot );

		void move(Dot &dot);

		void hittingTheEnemy(Enemy &enemy);
		void hittingTheEnemyBullet(EnemyBullet &enemybullet);

		inline void setVelY(int v){mVelY = v;};

    private:
		int mVelX, mVelY;
};



#endif /* BULLET_H_ */
