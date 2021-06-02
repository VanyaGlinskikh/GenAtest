#ifndef DOT_H_
#define DOT_H_

//The dot that will move around on the screen
#include "global.h"
#include "LTexGlobal.h"


class EnemyBullet;
class Enemy;
class SensorForPlayer;
class Dot
{
    public:
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		static const int DOT_VEL = 10;



		Dot();

		void handleEvent( SDL_Event& e);

		void move(std::vector<std::shared_ptr<Enemy>> enemy);
		void hittingTheDot(EnemyBullet &enemyBullet, Enemy &enemy);

		void render();
		int getHealth(){return _helth;};
		void setHealth(){ _helth--;};
		void resetHealth(){ _helth = 100;};
		int getMPosX();
		int getMPosY();

    private:
		int mPosX, mPosY;
		int mVelX, mVelY;
		int _helth;
		SensorForPlayer *sensorForPlayer;
};
#endif
