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
	setTexture(&gBulletTexture);
	setDimensions(WIDTH, HEIGHT);
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
	if ( rect().overlaps(enemy.rect())) {
//		std::cout<<"убил"<<std::endl;
		enemy.setPosX(); // FIXME: убрать эту гадость!
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
	if ( rect().overlaps(enemyBullet.rect())) {
//		std::cout<<"убил"<<std::endl;
		enemyBullet.setPosition(-50, -50); // FIXME: сделать по-человечески
//			mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
//		enemyBullet.setVelY(0);
		setPosition(-1000, -1000); // FIXME: сделать по-человечески
	}
}
