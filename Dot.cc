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

    mVelX = -3;
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


    //Move the dot left or right
//	mPosX += mVelX;
//	mVelX = 0;
//	mVelY = 0;
//	for (unsigned i = 0; i < enemyIdOnTheField.size(); ++i) {
////		sensorForPlayer->location(*enemy[enemyIdOnTheField[i]], mPosX, mPosY);
//		if (sensorForPlayer->location(*enemy[enemyIdOnTheField[i]], mPosX, mPosY) != -100 && enemy[enemyIdOnTheField[i]]->getMPosY()+20 < mPosY ){// если увидели противника и он находится впереди нас
//
//			if (enemy[enemyIdOnTheField[i]]->getMPosX()+20 > mPosX && mPosX+20 > enemy[enemyIdOnTheField[i]]->getMPosX()){
//				// когда противник находится прямо перед нами
//				setShot(true);
//				mVelX = 0;
//				mVelY = 0;
////				setVoidShot(true);
//				std::cout<<" стреляю "<<std::endl;
//			}
//			else if(mPosX+20 < enemy[enemyIdOnTheField[i]]->getMPosX()){
//				// если противник стоит правее
//				mVelX = 3;
//				mVelY = 0;
//				setShot(false);
////				setVoidShot(true);
//				std::cout<<" ухожу вправо"<<std::endl;
//			}
//			else if(mPosX > enemy[enemyIdOnTheField[i]]->getMPosX()+ 20){
//				// если противник стоит левее
//				mVelX = -3;
//				mVelY = 0;
//				setShot(false);
////				setVoidShot(true);
//				std::cout<<" ухожу влево"<<std::endl;
//			}
//
//		}
//		else if (sensorForPlayer->location(*enemy[enemyIdOnTheField[i]], mPosX, mPosY) != -100 && enemy[enemyIdOnTheField[i]]->getMPosY()+ 20 > mPosY){ // если увидели противника и он находится за нами
//			mVelY = 3;
//			setShot(false);
////			setVoidShot(true);
//			std::cout<<" иду назад увидев противника"<<std::endl;
//		}
//		else if (!getVoidShot()){
//			// это действие выполняется самым первым, мы просто идем вперел со смещением влево
//
//			setShot(false);
//			mVelY = -3;
//			mVelX = 1;
//			if (SCREEN_HEIGHT-mPosY >= 450) // если мы почти дошли до одного края карты, то меняем переключатель
//				setVoidShot(true);
//			std::cout<<" иду вперед от нечего делать"<<std::endl;
//		}
//		else if (getVoidShot()){ // если мы попали сюда, то мы уже пришли до одного края карты и надо двигаться в другой
//			setShot(false);
//			mVelY = 3;
//			mVelX = -1;
//			if (SCREEN_HEIGHT-mPosY < 40) // дошли до другого края карты, можно менять переключатель
//				setVoidShot(false);
//			std::cout<<" иду назад от нечего делать "<<std::endl;
//		}
//
//	}


    if (position().x <= 0)
    	mVelX = 3;
    if (position().x + WIDTH >= SCREEN_WIDTH)
    	mVelX = -3;


//    if (mPosX + DOT_WIDTH != SCREEN_WIDTH)
//		mPosX -= mVelX;
//    If the dot went too far to the left or right
//    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
//    {
////        //Move back
//        mPosX -= mVelX;
//    }

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
