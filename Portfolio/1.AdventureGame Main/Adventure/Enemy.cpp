#include "Enemy.h"
#include "window.h"
#include <time.h>

Enemy::Enemy()
{
	m_Health = 0;
	m_Damage = 0;
	m_Speed = 0;
	m_Death = false;

};


Enemy::~Enemy()
{
};

int Enemy::getSpeed() {return m_Speed ;}
int Enemy::getDamage(){return m_Damage;}
int Enemy::getHealth(){return m_Health;}
bool Enemy::getDeath() { return m_Death; }
bool Enemy::getBlocking() { return m_Blocking; }

bool Enemy::getDisarmed() { return m_Disarmed; }

bool Enemy::getDisarming() { return m_Disarming; }

void Enemy::setDeath(bool a_death) { m_Death = a_death; };
void Enemy::setHealth(int a_damage) { m_Health = a_damage; }
void Enemy::setBlock(bool a_blocking) { m_Blocking = a_blocking; }

void Enemy::setDisarmed(bool a_disarmed) { m_Disarmed = a_disarmed; }

void Enemy::setDisarming(bool a_disarming) { m_Disarming = a_disarming; }

static int enemyId = 1;

Spawn::Spawn() {

	idFind = rand() % 3;
	if (idFind == 0) {
		id = SKELETON;
		name.setString("Skeleton");
		spawnedId = id + enemyId++ * 10;
		m_Health = 20;
		m_Damage = 7;
		m_Speed = 4;
		m_MissChance = rand() % 30;
		m_Death = false;
		m_Disarmed = false;
	}
	if (idFind == 1) {
		id = ZOMBIE;
		name.setString("Zombie");
		spawnedId = id + enemyId++* 10;
		m_Health = 40;
		m_Damage = 10;
		m_Speed = 12;
		m_MissChance = rand() % 10;
		m_Death = false;
		m_Disarmed = false;

	}
	if (idFind == 2) {
		id = CRAZED;
		name.setString("Crazed");
		spawnedId = id + enemyId++* 10 ;
		m_Health = 30;
		m_Damage = 10;
		m_Speed = 5;
		m_MissChance = rand() % 50;
		m_Death = false;
		m_Disarmed = false;

	}
}
Spawn::Spawn(int a_spawnUnique) {

	
	if (a_spawnUnique == SKELETON) {
		id = SKELETON;
		name.setString("Skeleton");
		spawnedId = id + enemyId++* 10 ;
		m_Health = 20;
		m_Damage = 7;
		m_Speed = 6;
		m_MissChance = rand() % 30;
		m_Death = false;
		m_Disarmed = false;


	}
	if (a_spawnUnique == ZOMBIE) {
		id = ZOMBIE;
		name.setString("Zombie");
		spawnedId = id + enemyId++* 10 ;
		m_Health = 40;
		m_Damage = 10;
		m_Speed = 10;
		m_MissChance = rand() % 10;
		m_Death = false;
		m_Disarmed = false;

	}
	if (a_spawnUnique == CRAZED) {
		id = CRAZED;
		name.setString("Crazed");
		spawnedId = id + enemyId++* 10 ;
		m_Health = 30;
		m_Damage = 10;
		m_Speed = 5;
		m_MissChance = rand() % 50;
		m_Death = false;
		m_Disarmed = true;

	}
	if (a_spawnUnique == INNOCENT) {
		id = INNOCENT;
		name.setString("Innocent");
		spawnedId = id + enemyId++* 10 ;
		m_Health = 30;
		m_Damage = 2;
		m_Speed = 2;
		m_MissChance = (rand() % 8 + 10) *5;
		m_Death = false;
		m_Disarmed = true;

	}
	if (a_spawnUnique ==  DRAGON) {
		id = DRAGON;
		name.setString("Dragon!");
		spawnedId = id + enemyId++* 10 ;
		m_Health = 60;
		m_Damage = 15;
		m_Speed = 8;
		m_MissChance = rand() % 40;
		m_Death = false;
		m_Disarmed = true;

	}
}

int Spawn::getAttack() {
	int hitChance = rand() % 100;
	switch (id) {
	case SKELETON:

		if (hitChance > m_MissChance) {
			enum Attack {
				MELEE = 4, SWORD = 10, BLOCK = 0, MISS = -1, DISARM = -2
			};
			int currentDamage;
			int m_AttackProbability = rand() % 101;

			if (m_AttackProbability >= 0 && m_AttackProbability < 75) {
				if (m_Disarmed) {
					currentDamage = MELEE + rand() % 3;
					setBlock(false);
				}
				if (!m_Disarmed) {
					currentDamage = SWORD + rand() % 3;
					setBlock(false);

				}
			}
			if (m_AttackProbability >= 75 && m_AttackProbability < 97) {
				currentDamage = BLOCK;
				setBlock(true);

			}
			if (m_AttackProbability >= 97 && m_AttackProbability <= 100) {
				currentDamage = DISARM;
				setBlock(false);
				m_Disarming = true;
			}

			return currentDamage;
		}
		return -1;
		break;

	case ZOMBIE:

		if (hitChance > m_MissChance) {
			enum Attack {
				MELEE = 4, BITE = 6, MISS = -1,	};
			int currentDamage;
			int m_AttackProbability = rand() % 101;

			if (m_AttackProbability >= 0 && m_AttackProbability < 50) {

				currentDamage = MELEE + rand() % 3;
				setBlock(false);
				
			}
			if (m_AttackProbability >= 50 && m_AttackProbability <= 100) {
				currentDamage = BITE + rand() % 3;
				setBlock(false);

			}
			return currentDamage;
		}
		return -1;
		break;


	case CRAZED:

		if (hitChance > m_MissChance) {
			enum Attack {
				MELEE = 4, SWORD = 10, SHIELDBASH = 2, BLOCK = 0, MISS = -1, DISARM = -2};
			int currentDamage;
			int m_AttackProbability = rand() % 101;
			
			if (m_AttackProbability >= 0 && m_AttackProbability < 70) {
				if (m_Disarmed) {
					currentDamage = MELEE + rand() % 3;
					setBlock(false);
				}
				if (!m_Disarmed) {
					currentDamage = SWORD + rand() % 3;
					setBlock(false);
					 
				}
			}
			if (m_AttackProbability >= 70 && m_AttackProbability < 90) {
				currentDamage = SHIELDBASH + rand() % 3;
				setBlock(false);
				
				
			}
			if (m_AttackProbability >= 90 && m_AttackProbability < 97) {
				currentDamage = BLOCK;
				setBlock(true);

			}			
			if (m_AttackProbability >= 97 && m_AttackProbability <= 100) {
				currentDamage = DISARM;
				setBlock(false);
				m_Disarming = true;
			}

			return currentDamage;
		}
		return -1;
	
	case INNOCENT:

		if (hitChance > m_MissChance) {
			enum Attack {
				MELEE = 2, BLOCK = 0, MISS = -1, DISARM = -2
			};
			int currentDamage;
			int m_AttackProbability = rand() % 101;

			if (m_AttackProbability >= 0 && m_AttackProbability < 75) {
				if (m_Disarmed) {
					currentDamage = MELEE + rand() % 3;
					setBlock(false);
				}
			}
			if (m_AttackProbability >= 75 && m_AttackProbability < 97) {
				currentDamage = BLOCK;
				setBlock(true);

			}
			if (m_AttackProbability >= 97 && m_AttackProbability <= 100) {
				currentDamage = DISARM;
				setBlock(false);
				m_Disarming = true;
			}

			return currentDamage;
		}
		return -1;
	case DRAGON:

		if (hitChance > m_MissChance) {
			enum Attack {
			 BITE = 2, SLASH = 5, FIRE = 10, MISS = -1, DISARM = -2
			};
			int currentDamage;
			int m_AttackProbability = rand() % 101;

			if (m_AttackProbability >= 0 && m_AttackProbability < 75) {
				if (m_Disarmed) {
					currentDamage = BITE + rand() % 3;
					setBlock(false);
				}
			}
			if (m_AttackProbability >= 75 && m_AttackProbability < 97) {
				currentDamage = SLASH;
				setBlock(false);

			}
			if (m_AttackProbability >= 97 && m_AttackProbability <= 100) {
				currentDamage = FIRE;
				setBlock(false);
			}

			return currentDamage;
		}
	}
	return EXIT_FAILURE;
}
//Skeleton::Skeleton() {
//	m_Health = 20;
//	m_Damage = 10;
//	m_Speed = 5;
//}
//
//Skeleton::~Skeleton() {}
//
//void Skeleton::setBlock(bool a_blocking) { m_blocking = a_blocking; }
//
//bool Skeleton::getBlock() { return m_blocking; };
//
//int Skeleton::getAttack() {
//
//	
//
//Zombie::Zombie()
//{
//	m_Health = 40;
//	m_Damage = 6;
//	m_Speed = 8;
//}
//
//Zombie::~Zombie()
//{
//}
//
//int Zombie::getAttack()
//{
//	return 0;
//}
//
//Innocent::Innocent()
//{
//	m_Health = 15;
//	m_Damage = 2;
//	m_Speed = 4;
//}
//
//Innocent::~Innocent()
//{
//}
//
//int Innocent::getAttack()
//{
//	return 0;
//}
//
//Dragon::Dragon()
//{
//	m_Health = 80;
//	m_Damage = 15;
//	m_Speed = 7;
//}
//
//Dragon::~Dragon()
//{
//}
//
//int Dragon::getAttack()
//{
//	return 0;
//}
