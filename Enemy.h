/*
 * Enemy.h
 *
 *  Created on: 13 СЃРµРЅС‚. 2020 Рі.
 *      Author: vanya
 */

#ifndef ENEMY_H_
#define ENEMY_H_

//#include "Bullet.h"
#include "global.h"
#include "Genome.h"
#include "vector"
#include <functional>
#include "memory"
#include <chrono>
#include "Sprite.h"

class Sensor;
class Bullet;
class EnemyBullet;
class Dot;

class Enemy: public Sprite
{
	public:
		/*
		 * Функция актора. Вызывается существом в зависимости от текущего состояния.
		 * Параметр - ID существа.
		 */
		using ActorFunc = std::function<void(unsigned)>;
		/*
		 * Функция сенсора. Вызывается существом для получения входных данных.
		 * Параметр - ID существа.
		 */
		using SensorFunc = std::function<double(unsigned)>;
		static constexpr int WIDTH = 20;
		static constexpr int HEIGHT = 20;
		static constexpr int VELOCITY = 10;

		static constexpr unsigned MAX_ACTORS = 5;
		static_assert(MAX_ACTORS > 0, "MAX_ACTORS must not be zero");
//		static constexpr unsigned MAX_SENSORS = 4;
		static constexpr unsigned MAX_SENSORS = 6;

		static_assert(MAX_SENSORS > 0, "MAX_SENSORS must not be zero");
		static constexpr unsigned MAX_STATES = 128;
		static_assert(MAX_STATES >= MAX_ACTORS, "MAX_STATES must be >= MAX_ACTORS");
//		static constexpr unsigned PREDICATE_COUNT = 5;
		static constexpr unsigned PREDICATE_COUNT = 6;
		static_assert(PREDICATE_COUNT >= MAX_SENSORS, "PREDICATE_COUNT must be >= MAX_SENSORS");

		Enemy(unsigned id, Genome &genome);
		unsigned input();
		void tick();
		unsigned id() const { return _id; }
		void move(Bullet &bullet);

		bool predicatCheckBulletLeft(const std::vector<double>& data);
		bool predicatCheckBulletRight(const std::vector<double>& data);
		bool predicatCheckDotLeft(const std::vector<double>& data);
		bool predicatCheckDotRight(const std::vector<double>& data);
		bool predicatCheckAllyLeft(const std::vector<double>& data);
		bool predicatCheckAllyRight(const std::vector<double>& data);



		bool predicatCheckBullet(const std::vector<double>& data);
		bool predicatCheckDot(const std::vector<double>& data);
		bool predicatMove(const std::vector<double>& data);
		bool predicatCheckAlly(const std::vector<double>& data);
		bool predicatCheckAllyBullet(const std::vector<double>& data);



		void moveStraight();
		void moveBack();
		void moveRight();
		void moveLeft();
		void moveBull(EnemyBullet &enemyBullet);
		void moveShot(EnemyBullet &enemyBullet);
//		void add_actor(ActorFunc& actor) { _actors.push_back(actor); }
		void add_actor(ActorFunc& actor) {
			if (_real_actors_count == _actors.size()) { std::cout<<"перебор "; }
			_actors[_real_actors_count++] = actor; }
//		void add_sensor(SensorFunc sensor) { _sensors.push_back(sensor); }
		void add_sensor(SensorFunc sensor) {
			if (_real_sensor_count == _sensors.size()) { std::cout<<"перебор "; }
			_sensors[_real_sensor_count++] = sensor;}

//		void funk(std::vector<std::shared_ptr<Sensor>> sensors, Enemy &enemy, Bullet &bullet, Dot &dot);
		unsigned getSizeActors (){ return _actors.size();};

		// FIXME: убрать эту гадость!
		void setPosX(){ setPosition(-100, position().y); };
		void setPosY(){ setPosition(position().x, -100); };

		void setVelX(int v){ mVelX = v;};
		void setVelY(int v){ mVelY = v;};

		void setDead(bool v){_dead = v; };
		bool getDead(){return _dead; };

		void resetTickCount(){_tickCount = 0; };
		int getTickCount(){return _tickCount; };
		void upTickCount(){ _tickCount++; };

		void resetHittingTheDot(){_hitting_the_dot = 0; };
		int getHittingTheDot(){return _hitting_the_dot; };
		void upHittingTheDot(){ _hitting_the_dot++; };

		void resetHittingTheAlly(){_hitting_the_ally = 0; };
		int getHittingTheAlly(){return _hitting_the_ally; };
		void upHittingTheAlly(){ _hitting_the_ally++; };

		void resetShotCount(){ _shotCount = 0; };
		int getShotCount(){return _shotCount; };
		void upShotCount(){ _shotCount++;};

		void resetNumberOfMovements(){ _numberOfMovements = 0; };
		int getNumberOfMovements(){return _numberOfMovements; };
		void upNumberOfMovements(){ _numberOfMovements++;};

		void resetTotalNumberOfMovements(){ _totalNumberOfMovements = 0; };
		int getTotalNumberOfMovements(){return _totalNumberOfMovements; };
		void upTotalNumberOfMovements(){ _totalNumberOfMovements++;};

		void resetStandMovements(){ _standMovements = 0; };
		int getStandMovements(){return _standMovements; };
		void upStandMovements(){ _standMovements++;};

		void resetNumberOfDown(){ _numberOfDown = 0; };
		int getNumberOfDown(){return _numberOfDown; };
		void upNumberOfDown(){ _numberOfDown++;};

		void setEnemyOnTheField(bool v){_enemyOnTheField = v; };
		bool getEnemyOnTheField(){return _enemyOnTheField; };

		int getId(){return _id;};

		double fitnessFunction(const std::vector<double>& k){
			return	getHittingTheDot() * k[0] +
					getHittingTheAlly() * k[1] +
					getTickCount() * k[2] +
					getShotCount() * k[3] +
					getNumberOfMovements() * k[4] +
					getNumberOfDown()* k[5] +
					getStandMovements()* k[6];
		};


	protected:
		unsigned _id;
		Genome _genome;
		unsigned _real_actors_count = 0;
		unsigned _real_sensor_count = 0;

		unsigned _hitting_the_dot = 0;
		unsigned _hitting_the_ally = 0;
		// Список акторов
		std::vector<ActorFunc> _actors;
		// Список сенсоров
		std::vector<SensorFunc> _sensors;

		// Список акторов, выполняющихся в каждом из состояний
		std::vector<unsigned> _state_actions;
		// Таблица действий.
		// Первый индекс - текущее состояние
		// Второй индекс - входное значение
		std::vector<std::vector<unsigned>> _action_table;

		// Текущее состояние
		unsigned _state { 0U };

		bool _dead = false;
		unsigned _tickCount;
		unsigned _shotCount;
		bool _enemyOnTheField;
		int _numberOfMovements;
		int _totalNumberOfMovements;
		int _standMovements;
		int _numberOfDown;
	private:
		int mVelX, mVelY;

};




#endif /* ENEMY_H_ */
