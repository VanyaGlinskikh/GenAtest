/*
 * Bullet.cc
 *
 *  Created on: 23 янв. 2021 г.
 *      Author: vanya
 */
#include "EnemyBullet.h"
#include "Enemy.h"
#include "Bullet.h"
EnemyBullet::EnemyBullet()
{
	setTexture(&gEnemyBulletTexture);
	setDimensions(WIDTH, HEIGHT);

	//Initialize the offsets
	setPosition(-200, -200); // FIXME: убрать эту магию, сделать по-человечески

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

//void EnemyBullet::move(Enemy &enemy)
void EnemyBullet::move(int eX, int eY)
{
	// FIXME: убрать отсюда всю магию
	if (position().y == -50){
		setPosition(eX, eY);
	}

	if(position().y >= SCREEN_HEIGHT){
		setPosition(-200, -200);
		mVelY = 0;
	}

	translate(0, mVelY);
}

void EnemyBullet::hittingTheAlly(Enemy &enemy)
{
	if ( rect().overlaps(enemy.rect()) ) {
//		std::cout<<"убил своего"<<std::endl;
		enemy.setPosX(); // FIXME: убрать эту гадость!
		enemy.setPosY();
//			mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
		enemy.setVelX(0);
		enemy.setVelY(0);
		// FIXME: сделать по-человечески
		setPosition(-200, -200);
		enemy.setDead(true);
		enemy.setEnemyOnTheField(false);
		enemy.upHittingTheAlly();
		enemy.upShotCount();
	}
}

void EnemyBullet::hittingTheBullet(Bullet &bullet)
{
	if ( rect().overlaps(bullet.rect()) ) {
//		std::cout<<"убил своего"<<std::endl;
		bullet.setPosition(-50, -50);
		// FIXME: сделать по-человечески
		setPosition(-200, -200);
	}
}
