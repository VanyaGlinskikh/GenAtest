/*
 * Bullet.cc
 *
 *  Created on: 23 џэт. 2021 у.
 *      Author: vanya
 */
#include "Bullet.h"
Bullet::Bullet()
{
	    mPosX = 0;
	    mPosY = 1000;

	    mVelX = 0;
	    mVelY = 0;
}

int Bullet::getMPosX()
{
	return mPosX;
}

int Bullet::getMPosY()
{
	return mPosY;
}

void Bullet::handleEvent(SDL_Event& e,const Dot &dot)
{

	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	    {
	        //Adjust the velocity
	        switch( e.key.keysym.sym )
	        {
	        case SDLK_k: mPosY = dot.getMPosY();
			 	 	 	 mPosX = dot.getMPosX();
			 	 	 	 mVelY -= BULLET_VEL; break;
	        }
	    }
}

void Bullet::move(const Dot &dot)
{


	 if (mPosY >= -10)
		 mPosY += mVelY;
	 else{
		 mPosY = 1000;
		 mVelY = 0;
	 }


}

void Bullet::render()
{
    //Show the dot
	gBulletTexture.render(mPosX, mPosY);
}


