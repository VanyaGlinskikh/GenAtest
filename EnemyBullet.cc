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
	//Initialize the offsets

	    mPosX = -200;
	    mPosY = -200;

	    //Initialize the velocity
	    mVelX = 0;
	    mVelY = 0;
}

//void EnemyBullet::move(Enemy &enemy)
void EnemyBullet::move(int eX, int eY)
{
		if (mPosY == -50){
//			mPosX = enemy.getMPosX();
//			mPosY = enemy.getMPosY();
			mPosX = eX;
			mPosY = eY;

		}

		if(mPosY >= SCREEN_HEIGHT){
//			mPosX = enemy.getMPosX();
////			mPosY = enemy.getMPosY();
			mPosX = -200;
			mPosY = -200;
			mVelY = 0;

//
		}
//		if (enemy.getMPosY() <= 0)
//		if (eY <= 0)
//		{
//////			mPosX = enemy.getMPosX();
//////			mPosY = enemy.getMPosY();
//			mPosX = -200;
//			mPosY = -200;
//			mVelY = 0;
//		}


//		if (enemy.getMPosY() == 0)
//		if (eY== 0)
//		{
//////			mPosX = enemy.getMPosX();
//////			mPosY = enemy.getMPosY();
//			mPosX = eX;
//			mPosY = eY;
//			mVelY = 1;
//		}


		mPosY+=mVelY;

}

void EnemyBullet::hittingTheAlly(Enemy &enemy)
{
	if ( (mPosX+20 > enemy.getMPosX() &&  mPosX < enemy.getMPosX()+ 20) && mPosY < enemy.getMPosY())
			{

//		std::cout<<"убил своего"<<std::endl;
				enemy.setPosX();
				enemy.setPosY();
	//			mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
				enemy.setVelX(0);
				enemy.setVelY(0);
				mPosY = -200;
				mPosX = -200;
				enemy.setDead(true);
				enemy.setEnemyOnTheField(false);
				enemy.upHittingTheAlly();
				enemy.upShotCount();


	//			mVelY = 0;
			}
}

void EnemyBullet::hittingTheBullet(Bullet &bullet)
{
	if ( (mPosX+20 > bullet.getMPosX() &&  mPosX < bullet.getMPosX()+ 20) && mPosY < bullet.getMPosY())
			{

//		std::cout<<"убил своего"<<std::endl;
		bullet.setPosX(-50);
		bullet.setPosY(-50);
	//			mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
				mPosY = -200;
				mPosX = -200;


	//			mVelY = 0;
			}
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


