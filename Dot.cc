/*
 * Dot.cc
 *
 *  Created on: 23 янв. 2021 г.
 *      Author: vanya
 */

#include "Dot.h"
#include "EnemyBullet.h"
#include "Enemy.h"

LTexture gDotTexture;
Dot::Dot()
{
    mPosX = 0;
    mPosY = 200;
    _helth = 5;

    mVelX = 0;
    mVelY = 0;
}

int Dot::getMPosX()
{
	return mPosX;
}

int Dot::getMPosY()
{
	return mPosY;
}

void Dot::handleEvent( SDL_Event& e)
{

    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
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
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;

        }
    }
}

void Dot::move()
{


    //Move the dot left or right
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }

}


void Dot::hittingTheDot(EnemyBullet &enemyBullet, Enemy &enemy)
{
	  if ( (enemyBullet.getMPosX()+20 > mPosX &&  enemyBullet.getMPosX() < mPosX+ 20) && enemyBullet.getMPosY()+20 > mPosY && enemyBullet.getMPosY() < mPosY+20 )
	    {
	    	std::cout<<"в тебя попали"<<std::endl;
	    	if (getHealth() > 0)
	    		setHealth();
	    	if (getHealth() == 0)
				mPosX = -100;
	    	enemyBullet.setPosY(-200);
	    	enemyBullet.setPosX(-200);
	    	enemy.upHittingTheDot();

	    }
}

void Dot::render()
{
	gDotTexture.render( mPosX, mPosY );
}



