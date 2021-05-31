/*
 * Bullet.cc
 *
 *  Created on: 23 янв. 2021 г.
 *      Author: vanya
 */
#include "Bullet.h"
#include "Dot.h"
#include "Enemy.h"
#include "EnemyBullet.h"
Bullet::Bullet()
{
	    mPosX = 0;
	    mPosY = 1000;

	    mVelX = 0;
	    mVelY = 0;
}


void Bullet::handleEvent(SDL_Event& e, Dot &dot)
{

	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	    {
	        //Adjust the velocity
	        switch( e.key.keysym.sym )
	        {
	        case SDLK_z: mPosY = dot.getMPosY();
			 	 	 	 mPosX = dot.getMPosX();
			 	 	 	 mVelY -= BULLET_VEL; break;
	        }
	    }
}

int Bullet::getMPosX()
{
	return mPosX;
}

int Bullet::getMPosY()
{
	return mPosY;
}



void Bullet::move(Dot &dot)
{


	 if (mPosY >= -10)
		 mPosY += mVelY;
	 else{
		 mPosY = 1000;
		 mVelY = 0;
	 }
}
void Bullet::hittingTheEnemy(Enemy &enemy)
{
	if ( (mPosX+20 > enemy.getMPosX() &&  mPosX < enemy.getMPosX()+ 20) && mPosY < enemy.getMPosY()+20 && mPosY+20 > enemy.getMPosY())
		{
//		std::cout<<"убил"<<std::endl;
			enemy.setPosX();
			enemy.setPosY();
//			mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
			enemy.setVelX(0);
			enemy.setVelY(0);
			mPosY = -1000;
			mPosX = -1000;
			enemy.setDead(true);
			enemy.setEnemyOnTheField(false);

		}
}

void Bullet::hittingTheEnemyBullet(EnemyBullet &enemyBullet)
{
	if ( (mPosX+20 > enemyBullet.getMPosX() &&  mPosX < enemyBullet.getMPosX()+ 20) && mPosY < enemyBullet.getMPosY()+20 && mPosY+20 > enemyBullet.getMPosY())
		{
//		std::cout<<"убил"<<std::endl;
		enemyBullet.setPosX(-50);
		enemyBullet.setPosY(-50);
//			mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
//		enemyBullet.setVelY(0);
			mPosY = -1000;
			mPosX = -1000;

		}
}

void Bullet::render()
{
    //Show the dot
	gBulletTexture.render(mPosX, mPosY);
}


