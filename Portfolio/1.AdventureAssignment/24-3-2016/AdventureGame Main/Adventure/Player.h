#pragma once
class Player
{
public:
	Player();
	~Player();

	 bool getDeath();
	 int getSpeed();
	 int getDamage();
	 int getHealth();
	 bool getArmed();
	 void setDeath(bool a_death);
	 void setArmed(bool a_armed);
	 void setHealth(int a_health);

private:
	int m_playerHealth;
	int m_playerDamage;
	int m_playerSpeed ;
	bool m_playerDeath;
	bool m_playerArmed;
};

