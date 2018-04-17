#pragma once
#include <SFML/Graphics.hpp>
const float speed = 2;
class Bullet
{
	sf::Vector2f position;
	sf::Vector2f direction;

	sf::CircleShape shape;

public:
	Bullet(sf::Vector2f position = sf::Vector2f(0,0));
	~Bullet();

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;

};

