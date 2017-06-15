#include "Player.h"
#include "window.h"


Player::Player()
{
	m_playerHealth = 50;
	m_playerDamage = 20;
	m_playerSpeed = 5;
	m_playerDeath = false;
	m_playerArmed = true;
};


Player::~Player()
{
};
bool Player::getDeath() { return m_playerDeath; }
int Player::getSpeed() { return m_playerSpeed; }
int Player::getDamage() { return m_playerDamage; }
int Player::getHealth() { return m_playerHealth; }
bool Player::getArmed() { return m_playerArmed; }

void Player::setDeath(bool a_death) { m_playerDeath = a_death; }
void Player::setHealth(int a_health) { m_playerHealth = a_health; }
void Player::setArmed(bool a_armed) { m_playerArmed = a_armed; }