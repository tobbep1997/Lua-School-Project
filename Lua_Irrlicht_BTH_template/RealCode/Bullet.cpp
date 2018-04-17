#include "Bullet.h"



Bullet::Bullet(sf::Vector2f position)
{
	shape = sf::CircleShape(1.0f);
	shape.setPosition(position);
	this->position = position;
	shape.setFillColor(sf::Color::Black);
}


Bullet::~Bullet()
{
}

void Bullet::update()
{
	position += direction;
	this->shape.setPosition(position);
}

void Bullet::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(shape);
}
