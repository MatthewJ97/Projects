#pragma once
#include "string.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	int getSpeed();
	int getDamage();
	int getHealth();
	bool getDeath();
	bool getBlocking();
	bool getDisarmed();
	bool getDisarming();

	void setDeath(bool a_death);
	void setHealth(int a_damage);
	void setBlock(bool a_blocking);
	void setDisarmed(bool a_disarmed);
	void setDisarming(bool a_disarming);


protected:
	int m_Health;
	int m_Damage;
	int m_Speed;
	int m_MissChance;
	bool m_Blocking;
	bool m_Death;
	bool m_Disarmed;
	bool m_Disarming;


};

enum Etype { SKELETON, ZOMBIE, CRAZED, INNOCENT, DRAGON };

class Spawn : public Enemy {
public:
	Spawn();
	Spawn(int a_spawnUnique);
	int getAttack();
	~Spawn()  {};
	String name;

private:
	Etype id;
	int idFind;
	int spawnedId;
};


//class Skeleton : public Enemy {
//public:
//	Skeleton();
//	Skeleton(Skeleton &p_s) = delete;
//	~Skeleton();
//	int getAttack();
//	bool getBlock();
//	void setBlock(bool a_blocking);
//
//private:
//	bool m_blocking;
//
//};
//
//class Zombie : public Enemy {
//public:
//	Zombie();
//	~Zombie();
//	int getAttack();
//
//private:
//	
//
//};
//class Innocent : public Enemy {
//public:
//	Innocent();
//	~Innocent();
//	int getAttack();
//
//private:
//
//
//};
//class Dragon : public Enemy {
//public:
//	Dragon();
//	~Dragon();
//	int getAttack();
//
//private:
//
//
//};