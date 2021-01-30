/*
 * Bullet.cc
 *
 *  Created on: 23 џэт. 2021 у.
 *      Author: vanya
 */
#include "EnemyBullet.h"
#include "Enemy.h"
EnemyBullet::EnemyBullet()
{
	//Initialize the offsets

	    mPosX = 0;
	    mPosY = -50;

	    //Initialize the velocity
	    mVelX = 0;
	    mVelY = 0;
}

void EnemyBullet::move(Enemy &enemy)
{
		if (mPosY == -50){
			mPosX = enemy.getMPosX();
			mPosY = enemy.getMPosY();
		}



		if(mPosY >= SCREEN_HEIGHT){
			mPosX = enemy.getMPosX();
			mPosY = enemy.getMPosY();
		}
		if (enemy.getMPosY() <= 0)
		{
			mPosX = enemy.getMPosX();
			mPosY = enemy.getMPosY();
			mVelX = 0;
		}


		if (enemy.getMPosY() == 0)
		{
			mPosX = enemy.getMPosX();
			mPosY = enemy.getMPosY();
			mVelX = 2;
		}


		mPosY+=mVelX;

}
int EnemyBullet::getMPosX()
{
	return mPosX;
}

int EnemyBullet::getMPosY()
{
	return mPosY;
}

void EnemyBullet::render()
{
    //Show the dot
	gEnemyBulletTexture.render(mPosX, mPosY);
}


