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

    _health = 1000;

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

void Dot::move(	std::vector<std::shared_ptr<Enemy> > &enemy,
				std::vector<int> &enemyIdOnTheField,
				std::vector<EnemyBullet> &enemyBullet,
				int control_mode)
{
	switch(control_mode) {
	// Туда-сюда по всему экрану
	case CTRL_MODE_1:
	case CTRL_MODE_3:
	    if (position().x <= 0)
	    	mVelX = 3;
	    if (position().x + WIDTH >= SCREEN_WIDTH)
	    	mVelX = -3;
	    break;

	// Туда-сюда в левой части экрана
	case CTRL_MODE_5:
	case CTRL_MODE_6:
	    if (position().x <= 0)
	    	mVelX = 3;
	    if (position().x + WIDTH >= SCREEN_WIDTH/2)
	    	mVelX = -3;
	    break;

	// Туда-сюда в правой части экрана
	case CTRL_MODE_7:
	case CTRL_MODE_8:
	    if (position().x <= SCREEN_WIDTH/2)
	    	mVelX = 3;
	    if (position().x + WIDTH >= SCREEN_WIDTH)
	    	mVelX = -3;
	    break;

	case CTRL_MODE_2:
	case CTRL_MODE_4:
		mVelX = 0;
	    if (position().x < SCREEN_WIDTH / 2)
	    	mVelX = 3;
	    if (position().x > SCREEN_WIDTH / 2 + abs(mVelX))
	    	mVelX = -3;
	    break;

	case CTRL_MODE_MANUAL:
		;

	default:
		;
	}

    // Перемещаемся
	translate(mVelX, mVelY);

	if (control_mode == CTRL_MODE_MANUAL) {
		// Если уехали слишком далеко по вертикали, возвращаемся обратно
		if( ( position().y < 0 ) || ( position().y + HEIGHT >= SCREEN_HEIGHT ) )
			translate(0, -mVelY);

		// Если уехали слишком далеко по горизонтали, возвращаемся обратно
		if( ( position().x < 0 ) || ( position().x + WIDTH >= SCREEN_WIDTH ) )
			translate(-mVelX, 0);
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
