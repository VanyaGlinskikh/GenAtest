/*
 * Bullet.cc
 *
 *  Created on: 23 янв. 2021 г.
 *      Author: vanya
 */
#include "EnemyBullet.h"
#include "Enemy.h"
EnemyBullet::EnemyBullet()
{
	//Initialize the offsets

	    mPosX = -50;
	    mPosY = -50;

	    //Initialize the velocity
	    mVelX = 1;
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
//			mPosY = enemy.getMPosY();
			mPosX = eX;
			mPosY = eY;

		}
//		if (enemy.getMPosY() <= 0)
		if (eY <= 0)
		{
//			mPosX = enemy.getMPosX();
//			mPosY = enemy.getMPosY();
			mPosX = eX;
			mPosY = eY;
			mVelX = 0;
		}


//		if (enemy.getMPosY() == 0)
		if (eY== 0)
		{
//			mPosX = enemy.getMPosX();
//			mPosY = enemy.getMPosY();
			mPosX = eX;
			mPosY = eY;
			mVelX = 2;
		}


		mPosY+=mVelX;

}

void EnemyBullet::hittingTheAlly(Enemy &enemy)
{
	if ( (mPosX+20 > enemy.getMPosX() &&  mPosX < enemy.getMPosX()+ 20) && mPosY < enemy.getMPosY())
			{

		std::cout<<"убил своего"<<std::endl;
				enemy.setPosX();
				enemy.setPosY();
	//			mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
				enemy.getVelX(0);
				enemy.getVelY(0);
				mPosY = 1000;


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


