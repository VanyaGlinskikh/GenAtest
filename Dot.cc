/*
 * Dot.cc
 *
 *  Created on: 23 ���. 2021 �.
 *      Author: vanya
 */

#include "Dot.h"
#include "EnemyBullet.h"
#include "Enemy.h"
#include "SensorForPlayer.h"

LTexture gDotTexture;
Dot::Dot()
{
	sensorForPlayer = new SensorForPlayer;
    mPosX = 100;
    mPosY = 400;
    _helth = 100;

    mVelX = 0;
    mVelY = 0;
    _shot = false;
    _voidShot = false;
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
//        std::cout<<"1 ���������� bullet.mVelY: "<<bullet.mVelY<<" "<<mPosY<<std::endl;
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

void Dot::move(std::vector<std::shared_ptr<Enemy>> enemy, std::vector<int> &enemyIdOnTheField, std::vector<EnemyBullet> &enemyBullet)
{


    //Move the dot left or right
//	mPosX += mVelX;
	mVelX = 0;
	mVelY = 0;
	for (unsigned i = 0; i < enemyIdOnTheField.size(); ++i) {
//		sensorForPlayer->location(*enemy[enemyIdOnTheField[i]], mPosX, mPosY);
		if (sensorForPlayer->location(*enemy[enemyIdOnTheField[i]], mPosX, mPosY) != -100 && enemy[enemyIdOnTheField[i]]->getMPosY()+20 < mPosY ){// ���� ������� ���������� � �� ��������� ������� ���

			if (enemy[enemyIdOnTheField[i]]->getMPosX()+20 > mPosX && mPosX+20 > enemy[enemyIdOnTheField[i]]->getMPosX()){
				// ����� ��������� ��������� ����� ����� ����
				setShot(true);
				mVelX = 0;
				mVelY = 0;
//				setVoidShot(true);
				std::cout<<" ������� "<<std::endl;
			}
			else if(mPosX+20 < enemy[enemyIdOnTheField[i]]->getMPosX()){
				// ���� ��������� ����� ������
				mVelX = 3;
				mVelY = 0;
				setShot(false);
//				setVoidShot(true);
				std::cout<<" ����� ������"<<std::endl;
			}
			else if(mPosX > enemy[enemyIdOnTheField[i]]->getMPosX()+ 20){
				// ���� ��������� ����� �����
				mVelX = -3;
				mVelY = 0;
				setShot(false);
//				setVoidShot(true);
				std::cout<<" ����� �����"<<std::endl;
			}

		}
		else if (sensorForPlayer->location(*enemy[enemyIdOnTheField[i]], mPosX, mPosY) != -100 && enemy[enemyIdOnTheField[i]]->getMPosY()+ 20 > mPosY){ // ���� ������� ���������� � �� ��������� �� ����
			mVelY = 3;
			setShot(false);
//			setVoidShot(true);
			std::cout<<" ��� ����� ������ ����������"<<std::endl;
		}
		else if (!getVoidShot()){
			// ��� �������� ����������� ����� ������, �� ������ ���� ������ �� ��������� �����

			setShot(false);
			mVelY = -3;
			mVelX = 1;
			if (SCREEN_HEIGHT-mPosY >= 450) // ���� �� ����� ����� �� ������ ���� �����, �� ������ �������������
				setVoidShot(true);
			std::cout<<" ��� ������ �� ������ ������"<<std::endl;
		}
		else if (getVoidShot()){ // ���� �� ������ ����, �� �� ��� ������ �� ������ ���� ����� � ���� ��������� � ������
			setShot(false);
			mVelY = 3;
			mVelX = -1;
			if (SCREEN_HEIGHT-mPosY < 40) // ����� �� ������� ���� �����, ����� ������ �������������
				setVoidShot(false);
			std::cout<<" ��� ����� �� ������ ������ "<<std::endl;
		}

	}


//    if (mPosX <= 0)
//    	mVelX = 3;
//    if (mPosX + DOT_WIDTH >= SCREEN_WIDTH)
//    	mVelX = -3;


//    if (mPosX + DOT_WIDTH != SCREEN_WIDTH)
//		mPosX -= mVelX;
//    If the dot went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
//        //Move back
        mPosX -= mVelX;
    }

    	mPosX += mVelX;


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
//	    	std::cout<<"� ���� ������"<<std::endl;
	    	if (getHealth() > 0)
	    		setHealth();
	    	if (getHealth() == 0)
				mPosX = -100;
	    	enemyBullet.setPosY(-200);
	    	enemyBullet.setPosX(-200);
	    	enemy.upHittingTheDot();
//	    	enemy.upShotCount();

	    }
}

void Dot::render()
{
	gDotTexture.render( mPosX, mPosY );
}



