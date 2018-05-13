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

sf::Vector2f Bullet::getPos() const
{
	return position;
}

sf::CircleShape Bullet::getShape()
{
	return shape;
}

void Bullet::update(const float deltaTime)
{
	position += direction * velocity * deltaTime;
	this->shape.setPosition(position);
}



void Bullet::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(shape);
}
