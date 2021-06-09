#ifndef DOT_H_
#define DOT_H_

//The dot that will move around on the screen
#include "global.h"
#include "LTexture.h"

class EnemyBullet;
class Enemy;
//class SensorForPlayer;
class Dot
{
    public:
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		static const int DOT_VEL = 10;



		Dot();

		void handleEvent( SDL_Event& e);

		void move(std::vector<std::shared_ptr<Enemy>> enemy, std::vector<int> &enemyIdOnTheField, std::vector<EnemyBullet> &enemyBullet);
		void hittingTheDot(EnemyBullet &enemyBullet, Enemy &enemy);

		void render();
		int getHealth(){return _helth;};
		void setHealth(){ _helth--;};
		void resetHealth(){ _helth = 100;};
		int getMPosX();
		int getMPosY();

		void resetShot(){ _shot = 0; };
		bool getShot(){return _shot; };
		void setShot(bool v){ _shot = v;};

		void resetVoidShot(){ _voidShot = 0; };
		bool getVoidShot(){return _voidShot; };
		void setVoidShot(bool v){ _voidShot = v;};

    private:
		int mPosX, mPosY;
		int mVelX, mVelY;
		int _helth;
		bool _shot;
		bool _voidShot;
//		SensorForPlayer *sensorForPlayer;
};
#endif
