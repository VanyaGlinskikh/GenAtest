/*
 * Enemy.cc
 *
 *  Created on: 23 янв. 2021 г.
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

//void Enemy::funk(std::vector<std::shared_ptr<Sensor>> sensors, Enemy &enemy, Bullet &bullet, Dot &dot)
//{
////	std::cout<<"проверка работы 0 "<<sensors[0]<<std::endl;
////	std::cout<<"проверка работы 1 "<<sensors[1]<<std::endl;
//	if (auto vdbs = std::dynamic_pointer_cast<VisionDotBulletSensor>(sensors[1])) {
//		vdbs->location(enemy, bullet);
//	}
//	if (auto ves = std::dynamic_pointer_cast<VisionEnemySensor>(sensors[0])) {
//		ves->location(enemy, dot);
//	}
////	if (auto cts = std::dynamic_pointer_cast<CheckTeammatesSensor>(sensors[2])) {
//
////	}
//}

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



