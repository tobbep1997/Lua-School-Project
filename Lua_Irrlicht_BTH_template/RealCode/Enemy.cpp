#include "Enemy.h"

Enemy::Enemy(const int posX , const int posY)
{
	shape.setPosition(posX, posY);
	shape.setRadius(20.0f);
	shape.setFillColor(sf::Color::Red);

	m_health = 100;
	m_attack = 10;
	m_position = sf::Vector2f(posX, posY);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
}

void Enemy::DamageEnemy(int damage)
{
	m_health -= damage;
}

int Enemy::getHealth()
{
	return m_health;
}

void Enemy::setHealth(int health)
{
	m_health = health;
}

int Enemy::getAttack()
{
	return m_attack;
}

void Enemy::setAttack(int attack)
{
	m_attack = attack;
}

void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}
