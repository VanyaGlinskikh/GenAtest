/*
 * Enemy.h
 *
 *  Created on: 13 сент. 2020 г.
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
class EnemyBullet;
class Dot;
class Enemy
{
	public:
		/*
		 * ������� ������. ���������� ��������� � ����������� �� �������� ���������.
		 * �������� - ID ��������.
		 */
		using ActorFunc = std::function<void(unsigned)>;
		/*
		 * ������� �������. ���������� ��������� ��� ��������� ������� ������.
		 * �������� - ID ��������.
		 */
		using SensorFunc = std::function<double(unsigned)>;
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;
		static const int DOT_VEL = 3;

		static constexpr unsigned MAX_ACTORS = 4;
		static constexpr unsigned MAX_SENSORS = 5;
		static constexpr unsigned MAX_STATES = 4;
		static constexpr unsigned PREDICATE_COUNT = 9;

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
		bool predicatCheckWallRight(const std::vector<double>& data);
		bool predicatCheckWallLeft(const std::vector<double>& data);
		bool predicatCheckWallUp(const std::vector<double>& data);
		bool predicatCheckWallDown(const std::vector<double>& data);



		void moveStraight();
		void moveRight();
		void moveLeft();
		void moveBull(EnemyBullet &enemyBullet);
//		void add_actor(ActorFunc& actor) { _actors.push_back(actor); }
		void add_actor(ActorFunc& actor) {
			if (_real_actors_count == _actors.size()) { std::cout<<"������� "; }
			_actors[_real_actors_count++] = actor; }
//		void add_sensor(SensorFunc sensor) { _sensors.push_back(sensor); }
		void add_sensor(SensorFunc sensor) {
			if (_real_sensor_count == _sensors.size()) { std::cout<<"������� "; }
			_sensors[_real_sensor_count++] = sensor;}

//		void funk(std::vector<std::shared_ptr<Sensor>> sensors, Enemy &enemy, Bullet &bullet, Dot &dot);
		unsigned getSizeActors (){ return _actors.size();};
		void setMPosX(){ mPosX = rand() % 620 + 1;};
		void setMPosY(){ mPosY = (rand() % 80 + 20);};

		void setPosX(){ mPosX = -100;};
		void setPosY(){ mPosY = -100;};

		void getVelX(int v){ mVelX = v;};
		void getVelY(int v){ mVelY = v;};

		int getMPosX();
		int getMPosY();

	protected:
		unsigned _id;
		Genome _genome;
		unsigned _real_actors_count = 0;
		unsigned _real_sensor_count = 0;
		// ������ �������
		std::vector<ActorFunc> _actors;
		// ������ ��������
		std::vector<SensorFunc> _sensors;

		// ������ �������, ������������� � ������ �� ���������
		std::vector<unsigned> _state_actions;
		// ������� ��������.
		// ������ ������ - ������� ���������
		// ������ ������ - ������� ��������
		std::vector<std::vector<unsigned>> _action_table;

		// ������� ���������
		unsigned _state { 0U };
	private:
		int mPosX, mPosY;
		int mVelX, mVelY;
};




#endif /* ENEMY_H_ */
