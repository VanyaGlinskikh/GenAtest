/*
 * Enemy.cc
 *
 *  Created on: 23 янв. 2021 г.
 *      Author: vanya
 */
#include "Enemy.h"
#include "Bullet.h"
#include "Dot.h"
#include "EnemyBullet.h"
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


    mPosX = -300;
    mPosY = -300;

    _enemyOnTheField= false;


//    mPosX = rand() % 620 + 1;
//    mPosY = (rand() % 80 + 20);


   _tickCount = 0;
   _shotCount = 0;


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
	if (mPosY+20 != SCREEN_HEIGHT)
		mPosY += mVelY;
}

void Enemy::moveBack()
{
	if (mPosY != 0)
		mPosY -= mVelY;
}

void Enemy::moveRight()
{
	if (mPosX+20 != SCREEN_WIDTH)
		mPosX += mVelX;
}

void Enemy::moveLeft()
{
	if (mPosX != 0)
		mPosX -= mVelX;

}


void Enemy::moveBull(EnemyBullet &enemyBullet)
{

		enemyBullet.move(mPosX, mPosY);
//		if (enemyBullet.getMPosY() == -200)
////			upShotCount();
		enemyBullet.render();

}


void Enemy::moveShot(EnemyBullet &enemyBullet)
{
//	std::cout<<" значение Y у пули противника  "<<enemyBullet.getMPosY() << std::endl;
    if (enemyBullet.getMPosY() == -200){
    	upShotCount();
    	enemyBullet.setPosY(-50);
		enemyBullet.setVelY(1);
    }

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

bool Enemy::predicatMove(const std::vector<double>& data)// 1 - направо, 0 - налево
{
	std::random_device random_device;
	std::mt19937 engine{ random_device() };
	std::uniform_int_distribution<> rand(0, 1);
	if (predicatCheckBullet(data))
	{
		if ((data[1] ==  mPosX || data[1]+20 > mPosX) && data[1] > 0 && data[1] < mPosX)
			return 1;
		else
			return 0;

	}
	else if (predicatCheckDot(data))
	{
		if ( data[0]+20 > mPosX && data[0] > 0 && data[0] < mPosX)
			return 0;
		else
			return 1;

	}
	else if (predicatCheckAlly(data))
	{
		if ( data[2]+20 > mPosX && data[2] > 0 && data[2] < mPosX)
			return 1;
		else
			return 0;
	}
	else if (predicatCheckAllyBullet(data))
	{
		if ( data[3]+20 > mPosX && data[3] > 0 && data[3] < mPosX)
			return 1;
		else
			return 0;
	}
	else
		return rand(random_device);

}

bool Enemy::predicatCheckBullet(const std::vector<double>& data)// 1 - если двигаться при виде пули, 0 - если нет
{
	if (data[1]+ 20 > mPosX && data[1] < mPosX+20 )
		return 1;
	return 0;
}

//bool Enemy::predicatCheckBulletMove(const std::vector<double>& data) // 1 - если вправо, 0 - если налево
//{
//		if ((data[2] ==  mPosX || data[2]+20 > mPosX) && data[2] > 0 && data[2] < mPosX)
//			return 1;
//	return 0;
//}

bool Enemy::predicatCheckDot(const std::vector<double>& data)// 1 - если двигаться при виде врага, 0 - если нет
{
	if (data[0]+ 20 > mPosX && data[0] < mPosX+20 )
		return 0;
	return 1;
}

//bool Enemy::predicatCheckDotMove(const std::vector<double>& data) // 1 - если вправо, 0 - если налево
//{
//	if ( data[1]+20 > mPosX && data[1] > 0 && data[1] < mPosX)
//		return 0;
//	return 1;
//}

bool Enemy::predicatCheckAlly(const std::vector<double>& data)// 1 - если вправо, 0 - если налево
{
	if (data[2]+ 20 > mPosX && data[2] < mPosX+20 )
		return 1;
	return 0;
}

bool Enemy::predicatCheckAllyBullet(const std::vector<double>& data)// 1 - если вправо, 0 - если налево
{
	if (data[2]+ 20 > mPosX && data[2] < mPosX+20 )
		return 1;
	return 0;
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

bool Enemy::predicatCheckWallRight(const std::vector<double>& data)
{
	if (data[3] == mPosX+20)
		return 1;
	return 0;
}

bool Enemy::predicatCheckWallLeft(const std::vector<double>& data)
{
	if (data[3] == mPosX)
		return 1;
	return 0;
}

bool Enemy::predicatCheckWallUp(const std::vector<double>& data)
{
	if (data[4] == mPosY)
		return 1;
	return 0;
}

bool Enemy::predicatCheckWallDown(const std::vector<double>& data)
{
	if (data[4] == mPosX+20)
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
	pred |= (predicatCheckBullet(sensor_data));
	pred |= (predicatCheckDot(sensor_data)<<1);
	pred |= (predicatCheckAlly(sensor_data)<<2);
	pred |= (predicatMove(sensor_data)<<3);

//	pred |= (predicatAL(sensor_data));
//	pred |= (predicatAR(sensor_data) << 1);
//	pred |= (predicatIS(sensor_data) << 2);
//	pred |= (predicatCheckBulletRight(sensor_data) << 3);
//	pred |= (predicatCheckBulletLeft(sensor_data) << 4);
//	pred |= (predicatCheckWallRight(sensor_data) << 5);
//	pred |= (predicatCheckWallLeft(sensor_data) << 6);
//	pred |= (predicatCheckWallUp(sensor_data) << 7);
//	pred |= (predicatCheckWallDown(sensor_data) << 8);

	return pred;
}

void Enemy::tick()
{
	if (_dead) return;
	unsigned inp = input();
	unsigned new_state = _action_table[_state][inp] % MAX_STATES;
	_state = new_state;
	unsigned action = _state_actions[_state];
	_actors[action](_id);
	upTickCount();
}

void Enemy::render(/*double an, int ves*/)
{
//	if (ves == -100)
		gEnemyTexture.render( mPosX, mPosY);
//	else
//		gEnemyTexture.render( mPosX, mPosY, NULL, an);
}



