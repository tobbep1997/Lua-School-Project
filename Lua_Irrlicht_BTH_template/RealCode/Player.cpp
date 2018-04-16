#include "Player.h"

Player::Player(const int posX, const int posY)
{
	shape.setRadius(20.0f);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(posX, posY);

	m_health = 100;
	m_attack = 10;
	m_position = sf::Vector2f(posX,posY);
}


Player::~Player()
{
}

void Player::Update()
{
}
void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	target.draw(shape);

}

void Player::DamagePlayer(int damage)
{
	m_health -= damage;
}

void Player::GivePlayerHP(int hp)
{
	m_health += hp;
}


int Player::getHealth() const
{
	return m_health;
}

void Player::setHealth(int health)
{
	m_health = health;
}

int Player::getAttack() const
{
	return m_attack;
}

void Player::setAttack(int attack)
{
	m_attack = attack;
}


