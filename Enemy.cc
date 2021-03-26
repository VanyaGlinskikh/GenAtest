/*
 * Enemy.cc
 *
 *  Created on: 23 янв. 2021 г.
 *      Author: vanya
 */
#include "Enemy.h"
#include "Bullet.h"
#include "Dot.h"
#include "VisionDotBulletSensor.h"
#include "VisionEnemySensor.h"
#include "CheckTeammatesSensor.h"
Enemy::Enemy(unsigned id, Genome &genome)
:_id(id), _genome(genome)
{
	_sensors.resize(MAX_SENSORS);
	_actors.resize(MAX_ACTORS);

	std::fill(_sensors.begin(), _sensors.end(),
			[](unsigned) -> double { return 0.; });

	std::fill(_actors.begin(), _actors.end(),
			[](unsigned) {});

	_state_actions.resize(MAX_STATES);

	_action_table.resize(MAX_STATES);
	for (unsigned i = 0; i < MAX_STATES; ++i)
		_action_table[i].resize(1 << PREDICATE_COUNT);

	// Расшифровываем геном

	// Секция 0 - соответствие акторов состояниям
	for (unsigned i = 0; i < MAX_STATES; ++i)
		_state_actions[i] = (genome(0, i) & 0x0fffffff) % MAX_ACTORS;

	// Секция 1 - таблица действий конечного автомата
	for (unsigned i = 0; i < MAX_STATES; ++i)
		for (unsigned j = 0; j < (1 << PREDICATE_COUNT); ++j)
			_action_table[i][j] = (genome(1, i * (1 << PREDICATE_COUNT) + j) & 0x0fffffff) % MAX_STATES;

    mPosX = rand() % 620 + 1;
    mPosY = (rand() % 80 + 20);

    mVelX = 1;
    mVelY = 1;
}

int Enemy::getMPosX()
{
	return mPosX;
}

int Enemy::getMPosY()
{
	return mPosY;
}

void Enemy::moveStraight()
{

	mPosY += mVelY;
}

void Enemy::moveRight()
{
	mPosX += mVelX;
}

void Enemy::moveLeft()
{
	mPosX -= mVelX;

}

void Enemy::move(Bullet &bullet)
{
//	std::cout<<"координата противника X "<<getMPosX()<<"координата противника Y "<<getMPosY()<<std::endl;
	if(mPosY < 100)
		moveStraight();
	if ( (bullet.getMPosX()+20 > mPosX &&  bullet.getMPosX() < mPosX+ 20) && bullet.getMPosY() < mPosY)
	{
		mPosX = rand() % 620 + 1;
		mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
		mVelY = 0;
	}

	if( ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
	{
		mPosX = rand() % 620 + 1;
		mPosY = -SCREEN_HEIGHT - (rand() % 80 + 20);
	}




}

bool Enemy::predicatAL(const std::vector<double>& data)
{
	if (data[0] > 0)
		return 1;
	return 0;
}

bool Enemy::predicatAR(const std::vector<double>& data)
{
	if (data[0] < 0)
		return 1;
	return 0;
}

bool Enemy::predicatIS(const std::vector<double>& data)
{
	if (data[1] != -100)
		return 1;
	return 0;
}

bool Enemy::predicatCheckBulletRight(const std::vector<double>& data)
{
	if ((data[2] ==  mPosX || data[2]+20 > mPosX) && data[2] > 0 && data[2] < mPosX)
		return 1;
	return 0;
}

bool Enemy::predicatCheckBulletLeft(const std::vector<double>& data)
{
	if (data[2] < mPosX+20  && data[2] > 0 && data[2] > mPosX)
		return 1;
	return 0;
}

unsigned Enemy::input()
{
	// Чтение данных с сенсоров
	std::vector<double> sensor_data(_sensors.size()); // Данные с сенсоров
	for (unsigned i = 0; i < sensor_data.size(); ++i)
		sensor_data[i] = _sensors[i](id());

	// Результаты выполнения функции предиката
	unsigned pred = 0;
	pred |= (predicatAL(sensor_data));
	pred |= (predicatAR(sensor_data) << 1);
	pred |= (predicatIS(sensor_data) << 2);
	pred |= (predicatCheckBulletRight(sensor_data) << 3);
	pred |= (predicatCheckBulletLeft(sensor_data) << 4);

	return pred;
}

void Enemy::tick()
{
	unsigned inp = input();
	unsigned new_state = _action_table[_state][inp] % MAX_STATES;
	_state = new_state;
	unsigned action = _state_actions[_state];
	_actors[action](_id);

	std::cout<<"действие "<<action<<" id противника "<<_id<<std::endl;
}

void Enemy::render(/*double an, int ves*/)
{
//	if (ves == -100)
		gEnemyTexture.render( mPosX, mPosY);
//	else
//		gEnemyTexture.render( mPosX, mPosY, NULL, an);
}



