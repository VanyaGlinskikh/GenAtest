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
		upNumberOfDown();
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

bool Enemy::predicatMove(const std::vector<double>& data)// 1 - направо, 0 - налево
{
	std::random_device random_device;
	std::mt19937 engine{ random_device() };
	std::uniform_int_distribution<> rand(0, 1);
	if (predicatCheckBullet(data))
	{ // FIXME: что такое 20 ?
		if ((data[1] ==  position().x or data[1]+20 > position().x) and
				data[1] > 0 && data[1] < position().x)
			return 1;
		else
			return 0;

	}
	else if (predicatCheckDot(data))
	{ // FIXME: что такое 20 ?
		if ( data[0]+20 > position().x and data[0] > 0 && data[0] < position().x)
			return 0;
		else
			return 1;

	}
	else if (predicatCheckAlly(data))
	{ // FIXME: что такое 20 ?
		if ( data[2]+20 > position().x && data[2] > 0 && data[2] < position().x)
			return 1;
		else
			return 0;
	}
	else if (predicatCheckAllyBullet(data))
	{ // FIXME: что такое 20 ?
		if ( data[3]+20 > position().x && data[3] > 0 && data[3] < position().x)
			return 1;
		else
			return 0;
	}
	else
		return rand(random_device);


}

bool Enemy::predicatCheckBullet(const std::vector<double>& data)// 1 - если двигаться при виде пули, 0 - если нет
{ // FIXME: что такое 20 ?
	if (data[1]+ 20 > position().x && data[1] < position().x+20 )
		return 1;
	return 0;
}


bool Enemy::predicatCheckDot(const std::vector<double>& data)// 1 - если двигаться при виде врага, 0 - если нет
{
//	if (data[0]+ 20 > mPosX && data[0] < mPosX+20 )
//		return 0;
//	return 1;
	if (data[0] > 0 || data[1] > 0) // если в зоне видимости
		return 1;
	return 0;
}

bool Enemy::predicatCheckAlly(const std::vector<double>& data)// 1 - если вправо, 0 - если налево
{ // FIXME: что такое 20 ?
	if (data[2]+ 20 > position().x && data[2] < position().x+20 )
		return 1;
	return 0;
}

bool Enemy::predicatCheckAllyBullet(const std::vector<double>& data)// 1 - если вправо, 0 - если налево
{ // FIXME: что такое 20 ?
	if (data[2]+ 20 > position().x && data[2] < position().x+20 )
		return 1;
	return 0;
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
//	pred |= (predicatCheckBullet(sensor_data));
//	pred |= (predicatCheckDot(sensor_data)<<1);
//	pred |= (predicatCheckAlly(sensor_data)<<2);
//	pred |= (predicatMove(sensor_data)<<3);
	pred |= (predicatCheckBulletLeft(sensor_data));
	pred |= (predicatCheckBulletRight(sensor_data)<<1);
	pred |= (predicatCheckAllyLeft(sensor_data)<<2);
	pred |= (predicatCheckAllyRight(sensor_data)<<3);
	pred |= (predicatCheckDotLeft(sensor_data)<<4);
	pred |= (predicatCheckDotRight(sensor_data)<<5);
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
	if (getStandMovements() > IDLE_LIMIT){
		setDead(true);
		setEnemyOnTheField(false);
	}
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
		gEnemyTexture.render( position().x, position().y);
//	else
//		gEnemyTexture.render( mPosX, mPosY, NULL, an);
}



