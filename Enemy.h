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
#include <chrono>

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
		static const int DOT_VEL = 10;

		static constexpr unsigned MAX_ACTORS = 5;
		static_assert(MAX_ACTORS > 0, "MAX_ACTORS must not be zero");
		static constexpr unsigned MAX_SENSORS = 4;
		static_assert(MAX_SENSORS > 0, "MAX_SENSORS must not be zero");
		static constexpr unsigned MAX_STATES = 128;
		static_assert(MAX_STATES >= MAX_ACTORS, "MAX_STATES must be >= MAX_ACTORS");
		static constexpr unsigned PREDICATE_COUNT = 5;
		static_assert(PREDICATE_COUNT >= MAX_SENSORS, "PREDICATE_COUNT must be >= MAX_SENSORS");

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

		bool predicatCheckBullet(const std::vector<double>& data);
//		bool predicatCheckBulletMove(const std::vector<double>& data);
		bool predicatCheckDot(const std::vector<double>& data);
//		bool predicatCheckDotMove(const std::vector<double>& data);
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
			if (_real_actors_count == _actors.size()) { std::cout<<"������� "; }
			_actors[_real_actors_count++] = actor; }
//		void add_sensor(SensorFunc sensor) { _sensors.push_back(sensor); }
		void add_sensor(SensorFunc sensor) {
			if (_real_sensor_count == _sensors.size()) { std::cout<<"������� "; }
			_sensors[_real_sensor_count++] = sensor;}

//		void funk(std::vector<std::shared_ptr<Sensor>> sensors, Enemy &enemy, Bullet &bullet, Dot &dot);
		unsigned getSizeActors (){ return _actors.size();};
		void setMPosX(int r){ mPosX= r;};
//		mPosX = rand() % 620 + 1;
		void setMPosY(int r){mPosY= r; };
//		mPosY = (rand() % 80 + 20);

		void setPosX(){ mPosX = -100;};
		void setPosY(){ mPosY = -100;};

		void setVelX(int v){ mVelX = v;};
		void setVelY(int v){ mVelY = v;};

		int getMPosX();
		int getMPosY();

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

		void setEnemyOnTheField(bool v){_enemyOnTheField = v; };
		bool getEnemyOnTheField(){return _enemyOnTheField; };

		int getId(){return _id;};

//		bool k1 = getHittingTheDot()  > 0;
//		bool k2 = getHittingTheAlly() > 0;

		double k1 = 5.;
		double k2 = 4.;
		double k3 = 1.2;
		double k4 = 2.;
		double k5 = 1.1;

//		double fitnessFunction(){ return ((getHittingTheDot() *(k1? 2. : 1.)) - (getHittingTheAlly() * (k2? 2. : 1.)) + (1./getTickCount()) ); };
		double fitnessFunction(){ return getHittingTheDot() * k1 - getHittingTheAlly() * k2 /*+ getTickCount()*k3*/ + getShotCount() * k4 + getNumberOfMovements()*k5; };



	protected:
		unsigned _id;
		Genome _genome;
		unsigned _real_actors_count = 0;
		unsigned _real_sensor_count = 0;

		unsigned _hitting_the_dot = 0;
		unsigned _hitting_the_ally = 0;
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

		bool _dead = false;
		unsigned _tickCount;
		unsigned _shotCount;
		bool _enemyOnTheField;
		int _numberOfMovements;
	private:
		int mPosX, mPosY;
		int mVelX, mVelY;

};




#endif /* ENEMY_H_ */
