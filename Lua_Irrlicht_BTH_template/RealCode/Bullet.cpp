#include "Bullet.h"




Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction, float velocity)
{
	shape = sf::CircleShape(1.0f);
	shape.setPosition(position);
	this->position = position;
	this->direction = direction;
	shape.setFillColor(sf::Color::Magenta);
	this->velocity = velocity;
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	position += direction * velocity;
	this->shape.setPosition(position);
}

void Bullet::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(shape);
}
