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
	    mPosition.set(0, 1000);

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
	        case SDLK_z: mPosition.set(dot.getMPosX(), dot.getMPosY());
			 	 	 	 mVelY -= VELOCITY; break;
	        }
	    }
}

void Bullet::move(Dot &dot)
{


	 if (mPosition.y >= -10)
		 mPosition.translate(0, mVelY);
	 else{
		 mPosition.y = 1000;
		 mVelY = 0;
	 }
}
void Bullet::hittingTheEnemy(Enemy &enemy)
{
	if ( 	mPosition.x + WIDTH > enemy.getMPosX() and
			mPosition.x < enemy.getMPosX() + Enemy::DOT_WIDTH and
			mPosition.y < enemy.getMPosY() + Enemy::DOT_HEIGHT and
			mPosition.y + HEIGHT > enemy.getMPosY()) // TODO: заменить на Rectangle2D
		{
//		std::cout<<"убил"<<std::endl;
			enemy.setPosX();
			enemy.setPosY();
//			mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
			enemy.setVelX(0);
			enemy.setVelY(0);
			mPosition.set(-1000, -1000); // FIXME: сделать по-человечески

			enemy.setDead(true);
			enemy.setEnemyOnTheField(false);

		}
}

void Bullet::hittingTheEnemyBullet(EnemyBullet &enemyBullet)
{
	if (	mPosition.x + WIDTH > enemyBullet.getMPosX() and
			mPosition.x < enemyBullet.getMPosX() + EnemyBullet::BULLET_WIDTH and
			mPosition.y < enemyBullet.getMPosY() + EnemyBullet::BULLET_HEIGHT and
			mPosition.y + HEIGHT > enemyBullet.getMPosY()) // TODO: заменить на Rectangle2D
		{
//		std::cout<<"убил"<<std::endl;
		enemyBullet.setPosX(-50);
		enemyBullet.setPosY(-50);
//			mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
//		enemyBullet.setVelY(0);
			mPosition.set(-1000, -1000); // FIXME: сделать по-человечески
		}
}

void Bullet::render()
{
    //Show the dot
	gBulletTexture.render(mPosition.x, mPosition.y);
}


