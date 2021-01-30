/*
 * Enemy.cc
 *
 *  Created on: 23 џэт. 2021 у.
 *      Author: vanya
 */
#include "Enemy.h"
#include "Bullet.h"
Enemy::Enemy()
{


    mPosX = rand() % 620 + 1;
    mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);

    mVelX = 0;
    mVelY = 1;
}

int Enemy::getMPosX()
{
	return mPosX;
}

int Enemy::getMPosY()
{
	return mPosY;
}

void Enemy::funk()
{

}

void Enemy::move(Bullet &bullet)
{
//	if(mPosY < 100)
		mPosY += mVelY;
	if ( (bullet.getMPosX()+20 > mPosX &&  bullet.getMPosX() < mPosX+ 20) && bullet.getMPosY() < mPosY)
	{
		mPosX = rand() % 620 + 1;
		mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
		mVelY = 0;
	}

	if( ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
	{
		mPosX = rand() % 620 + 1;
		mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
	}




}

void Enemy::render()
{
	gEnemyTexture.render( mPosX, mPosY);
}



