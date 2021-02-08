/*
 * Enemy.cc
 *
 *  Created on: 23 ���. 2021 �.
 *      Author: vanya
 */
#include "Enemy.h"
#include "Bullet.h"
#include "Dot.h"
#include "VisionDotBulletSensor.h"
#include "VisionEnemySensor.h"
#include "CheckTeammatesSensor.h"
Enemy::Enemy()
{


    mPosX = rand() % 620 + 1;
    mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);

    mVelX = 5;
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

void Enemy::moveStraight()
{

	mPosY += mVelY;
}

void Enemy::moveRight()
{
	mPosX += mVelX;
}

void Enemy::moveLeft()
{
	mPosX -= mVelX;

}

void Enemy::move(Bullet &bullet)
{
//	std::cout<<"���������� ���������� X "<<getMPosX()<<"���������� ���������� Y "<<getMPosY()<<std::endl;
	if(mPosY < 100)
		moveStraight();
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

void Enemy::render(double an)
{
	gEnemyTexture.render( mPosX, mPosY, NULL, an);
}



