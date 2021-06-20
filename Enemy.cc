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
Enemy::Enemy(unsigned id, Genome &genome)
:_id(id), _genome(genome)
{
	setTexture(&gEnemyTexture);
	setDimensions(WIDTH, HEIGHT);

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


	// FIXME: сделать по-человечески
	setPosition(-300, -300);

    _enemyOnTheField= false;


   _tickCount = 0;
   _shotCount = 0;
   _numberOfMovements = 0;
   _totalNumberOfMovements = 0;
   _standMovements = 0;
   _numberOfDown = 0;


    mVelX = 1;
    mVelY = 1;
}

void Enemy::moveStraight()
{
	upTotalNumberOfMovements();
	if (position().y + HEIGHT != SCREEN_HEIGHT){
		translate(0, mVelY);
		upNumberOfMovements();
		resetStandMovements();
	}
	else
		upStandMovements();
}

void Enemy::moveBack()
{
	upTotalNumberOfMovements();
	if (position().y > 0){
		translate(0, -mVelY);
		upNumberOfDown();
		upNumberOfMovements();
		resetStandMovements();
	}
	else
		upStandMovements();
}

void Enemy::moveRight()
{
	upTotalNumberOfMovements();
	if (position().x+WIDTH != SCREEN_WIDTH){
		translate(mVelX, 0);
		upNumberOfMovements();
		resetStandMovements();
	}
	else
		upStandMovements();
}

void Enemy::moveLeft()
{
	upTotalNumberOfMovements();
	if (position().x > 0){
		translate(-mVelX, 0);
		upNumberOfMovements();
		resetStandMovements();
	}
	else
		upStandMovements();

}


void Enemy::moveBull(EnemyBullet &enemyBullet)
{

		enemyBullet.move(position().x, position().y);
		enemyBullet.render();

}


void Enemy::moveShot(EnemyBullet &enemyBullet)
{
    if (enemyBullet.position().y == -200){
    	upShotCount();
    	// FIXME: сделать по-человечески
    	enemyBullet.setPosition(enemyBullet.position().x, -50);
		enemyBullet.setVelY(1);
    }

}

void Enemy::move(Bullet &bullet)
{
//	std::cout<<"координата противника X "<<getMPosX()<<"координата противника Y "<<getMPosY()<<std::endl;
	if(position().y < 100)
		moveStraight();
	if (	bullet.position().x + Bullet::WIDTH > position().x and
			bullet.position().x < position().x + WIDTH and
			bullet.position().y < position().y)
	{
		setPosition(
				rand() % 620 + 1,
				-SCREEN_HEIGHT - (rand() % 80 + 20)); // FIXME: What is this I don't even
		mVelY = 0;
	}

	if( ( position().y + HEIGHT > SCREEN_HEIGHT ) )
	{
		setPosition(
				rand() % 620 + 1,
				-SCREEN_HEIGHT - (rand() % 80 + 20)); // FIXME: What is this I don't even
	}
}


bool Enemy::predicatCheckBulletLeft(const std::vector<double>& data)
{
	if (data[2]>0 && data[3]<0)
			return 1;
		return 0;
}
bool Enemy::predicatCheckBulletRight(const std::vector<double>& data)
{
	if (data[2]<0 && data[3]>0)
		return 1;
	return 0;
}

bool Enemy::predicatCheckDotLeft(const std::vector<double>& data)
{
	if (data[0]>0 && data[1]<0)
			return 1;
		return 0;
}
bool Enemy::predicatCheckDotRight(const std::vector<double>& data)
{
	if (data[0]<0 && data[1]>0)
		return 1;
	return 0;
}

bool Enemy::predicatCheckAllyLeft(const std::vector<double>& data)
{
	if (data[4]>0 && data[5]<0)
			return 1;
		return 0;
}
bool Enemy::predicatCheckAllyRight(const std::vector<double>& data)
{
	if (data[4]<0 && data[5]>0)
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

	pred |= (predicatCheckBulletLeft(sensor_data));
	pred |= (predicatCheckBulletRight(sensor_data)<<1);
	pred |= (predicatCheckAllyLeft(sensor_data)<<2);
	pred |= (predicatCheckAllyRight(sensor_data)<<3);
	pred |= (predicatCheckDotLeft(sensor_data)<<4);
	pred |= (predicatCheckDotRight(sensor_data)<<5);


	return pred;
}

void Enemy::tick(Genome &genome)
{
	if (getStandMovements() > IDLE_LIMIT){
		setDead(true);
		setEnemyOnTheField(false);
	}
	if (_dead) return;
	if (genome.getWithoutСhanges() > 10)
		setTexture(&gEnemyOldTexture);
	else
		setTexture(&gEnemyTexture);
	unsigned inp = input();
	unsigned new_state = _action_table[_state][inp] % MAX_STATES;
	_state = new_state;
	unsigned action = _state_actions[_state];
	_actors[action](_id);
	upTickCount();
}
