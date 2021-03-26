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
#include "LTexGlobal.h"
#include "Genome.h"
#include "vector"
#include <functional>
#include "memory"

class Sensor;
class Bullet;
class Dot;
class Enemy
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
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;
		static const int DOT_VEL = 3;

		static constexpr unsigned MAX_ACTORS = 3;
		static constexpr unsigned MAX_SENSORS = 3;
		static constexpr unsigned MAX_STATES = 4;
		static constexpr unsigned PREDICATE_COUNT = 5;

		Enemy(unsigned id, Genome &genome);
		unsigned input();
		void tick();
		unsigned id() const { return _id; }
		void move(Bullet &bullet);

		void render(/*double an, int ves*/);

		bool predicatAL(const std::vector<double>& data);
		bool predicatAR(const std::vector<double>& data);
		bool predicatIS(const std::vector<double>& data);
		bool predicatCheckBulletRight(const std::vector<double>& data);
		bool predicatCheckBulletLeft(const std::vector<double>& data);

		void moveStraight();
		void moveRight();
		void moveLeft();
		void add_actor(ActorFunc& actor) { _actors.push_back(actor); }
		void add_sensor(SensorFunc sensor) { _sensors.push_back(sensor); }

//		void funk(std::vector<std::shared_ptr<Sensor>> sensors, Enemy &enemy, Bullet &bullet, Dot &dot);

		int getMPosX();
		int getMPosY();

	protected:
		unsigned _id;
		Genome _genome;
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
	private:
		int mPosX, mPosY;
		int mVelX, mVelY;
};




#endif /* ENEMY_H_ */
