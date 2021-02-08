#ifndef DOT_H_
#define DOT_H_

//The dot that will move around on the screen
#include "global.h"
#include "LTexGlobal.h"
//#include "EnemyBullet.h"

class EnemyBullet;
class Dot
{
    public:
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		static const int DOT_VEL = 1;

		Dot();

		void handleEvent( SDL_Event& e);

		void move(EnemyBullet &enemyBullet);

		void render();

		int getMPosX();
		int getMPosY();

    private:
		int mPosX, mPosY;
		int mVelX, mVelY;
};
#endif
