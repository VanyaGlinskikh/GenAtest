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
	setPosition(0, 1000);

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
	        case SDLK_z: setPosition(dot.position());
			 	 	 	 mVelY -= VELOCITY; break;
	        }
	    }
}

void Bullet::move(Dot &dot)
{


	 if (position().y >= -10)
		 translate(0, mVelY);
	 else {
		 setPosition(position().x, 1000); // FIXME: сделать по-человечески
		 mVelY = 0;
	 }
}
void Bullet::hittingTheEnemy(Enemy &enemy)
{
	if ( 	position().x + WIDTH > enemy.getMPosX() and
			position().x < enemy.getMPosX() + Enemy::WIDTH and
			position().y < enemy.getMPosY() + Enemy::HEIGHT and
			position().y + HEIGHT > enemy.getMPosY()) // TODO: заменить на Rectangle2D
		{
//		std::cout<<"убил"<<std::endl;
			enemy.setPosX();
			enemy.setPosY();
//			mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
			enemy.setVelX(0);
			enemy.setVelY(0);
			setPosition(-1000, -1000); // FIXME: сделать по-человечески

			enemy.setDead(true);
			enemy.setEnemyOnTheField(false);

		}
}

void Bullet::hittingTheEnemyBullet(EnemyBullet &enemyBullet)
{
	if (	position().x + WIDTH > enemyBullet.getMPosX() and
			position().x < enemyBullet.getMPosX() + EnemyBullet::WIDTH and
			position().y < enemyBullet.getMPosY() + EnemyBullet::HEIGHT and
			position().y + HEIGHT > enemyBullet.getMPosY()) // TODO: заменить на Rectangle2D
		{
//		std::cout<<"убил"<<std::endl;
		enemyBullet.setPosX(-50);
		enemyBullet.setPosY(-50);
//			mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
//		enemyBullet.setVelY(0);
			setPosition(-1000, -1000); // FIXME: сделать по-человечески
		}
}

void Bullet::render()
{
    //Show the dot
	gBulletTexture.render(position().x, position().y);
}


