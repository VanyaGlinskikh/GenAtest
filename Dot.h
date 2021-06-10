#ifndef DOT_H_
#define DOT_H_

//The dot that will move around on the screen
#include "global.h"
#include "LTexture.h"
#include "Sprite.h"

class EnemyBullet;
class Enemy;
class SensorForPlayer;

class Dot: public Sprite
{
public:
	static const int WIDTH = 20;
	static const int HEIGHT = 20;

	static const int VELOCITY = 10;

	Dot();

	void handleEvent( SDL_Event& e);

	void move(std::vector<std::shared_ptr<Enemy>> enemy, std::vector<int> &enemyIdOnTheField, std::vector<EnemyBullet> &enemyBullet);
	void hittingTheDot(EnemyBullet &enemyBullet, Enemy &enemy);

	int getHealth(){return _health;};
	void setHealth(){ _health--;};
	void resetHealth(){ _health = 100;};

	void resetShot(){ _shot = 0; };
	bool getShot(){return _shot; };
	void setShot(bool v){ _shot = v;};

	void resetVoidShot(){ _voidShot = 0; };
	bool getVoidShot(){return _voidShot; };
	void setVoidShot(bool v){ _voidShot = v;};

private:
	int mVelX, mVelY;
	int _health;
	bool _shot;
	bool _voidShot;

	static constexpr int DEFAULT_X = 100;
	static constexpr int DEFAULT_Y = 340;
};
#endif
