/*
 * Dot.cc
 *
 *  Created on: 23 янв. 2021 г.
 *      Author: vanya
 */

#include "Dot.h"
#include "EnemyBullet.h"
#include "Enemy.h"
//#include "SensorForPlayer.h"

Dot::Dot()
{
	setTexture(&gDotTexture);
	setDimensions(WIDTH, HEIGHT);

//	sensorForPlayer = new SensorForPlayer;
	setPosition(DEFAULT_X, DEFAULT_Y);

    _health = 100;

    mVelX = 0;
    mVelY = 0;
    _shot = false;
    _voidShot = false;
}

void Dot::handleEvent( SDL_Event& e)
{

    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= VELOCITY; break;
            case SDLK_DOWN: mVelY += VELOCITY; break;
            case SDLK_LEFT: mVelX -= VELOCITY; break;
            case SDLK_RIGHT: mVelX += VELOCITY; break;

//            case SDLK_k: bullet.mVelY -= bullet.BULLET_VEL; break;

        }
//        std::cout<<"1 координаты bullet.mVelY: "<<bullet.mVelY<<" "<<mPosY<<std::endl;
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += VELOCITY; break;
            case SDLK_DOWN: mVelY -= VELOCITY; break;
            case SDLK_LEFT: mVelX += VELOCITY; break;
            case SDLK_RIGHT: mVelX -= VELOCITY; break;

        }
    }
}

void Dot::move(std::vector<std::shared_ptr<Enemy>> enemy, std::vector<int> &enemyIdOnTheField, std::vector<EnemyBullet> &enemyBullet)
{



    if (position().x <= 0)
    	mVelX = 3;
    if (position().x + WIDTH >= SCREEN_WIDTH)
    	mVelX = -3;

    //Move the dot
	translate(mVelX, mVelY);

    //If the dot went too far up or down
    if( ( position().y < 0 ) || ( position().y + HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        translate(0, -mVelY);
    }

}

void Dot::move2(std::vector<std::shared_ptr<Enemy>> enemy, std::vector<int> &enemyIdOnTheField, std::vector<EnemyBullet> &enemyBullet)
{

//    if (position().x + WIDTH != SCREEN_WIDTH)
//    	translate(-mVelX, 0);

    if( ( position().x < 0 ) || ( position().x + WIDTH > SCREEN_WIDTH ) )
    {

    	translate(-mVelX, 0);
    }

    //Move the dot
	translate(mVelX, mVelY);

    //If the dot went too far up or down
    if( ( position().y < 0 ) || ( position().y + HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        translate(0, -mVelY);
    }

}

void Dot::move6(std::vector<std::shared_ptr<Enemy>> enemy, std::vector<int> &enemyIdOnTheField, std::vector<EnemyBullet> &enemyBullet)
{



    if (position().x <= 0)
    	mVelX = 3;
    if (position().x + WIDTH >= SCREEN_WIDTH/2)
    	mVelX = -3;

    //Move the dot
	translate(mVelX, mVelY);

    //If the dot went too far up or down
    if( ( position().y < 0 ) || ( position().y + HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        translate(0, -mVelY);
    }

}

void Dot::move8(std::vector<std::shared_ptr<Enemy>> enemy, std::vector<int> &enemyIdOnTheField, std::vector<EnemyBullet> &enemyBullet)
{



    if (position().x <= SCREEN_WIDTH/2)
    	mVelX = 3;
    if (position().x + WIDTH >= SCREEN_WIDTH)
    	mVelX = -3;

    //Move the dot
	translate(mVelX, mVelY);

    //If the dot went too far up or down
    if( ( position().y < 0 ) || ( position().y + HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        translate(0, -mVelY);
    }

}


void Dot::hittingTheDot(EnemyBullet &enemyBullet, Enemy &enemy)
{
	if (rect().overlaps(enemyBullet.rect())) {
	//	    	std::cout<<"в тебя попали"<<std::endl;
		if (getHealth() > 0)
			setHealth();

		if (getHealth() == 0) // FIXME: сделать по-человечески
			setPosition(-100, position().y);

		// FIXME: сделать по-человечески
		enemyBullet.setPosition(-200, -200);
		enemy.upHittingTheDot();
	//	    	enemy.upShotCount();

	}
}
