/*
 * bullet.h
 *
 *  Created on: 21 янв. 2021 г.
 *      Author: vanya
 */

#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_

//#include "Enemy.h"
#include "global.h"
#include "Sprite.h"

class Enemy;
class Genome;
class Bullet;

class EnemyBullet: public Sprite
{
public:
	static constexpr int WIDTH = 20;
	static constexpr int HEIGHT = 20;
	static constexpr int BULLET_VEL = 10;

	EnemyBullet();
	EnemyBullet(const EnemyBullet&) = delete;
//		void move(Enemy &enemy);
	void move(int x, int y);
	void hittingTheAlly(Enemy &enemy);
	void hittingTheBullet(Bullet &bullet);


	void render();

	void setVelY(int v){mVelY = v;};

private:
	int mVelX, mVelY;
};



#endif /* BULLET_H_ */
