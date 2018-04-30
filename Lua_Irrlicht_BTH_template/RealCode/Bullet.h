#pragma once
#include <SFML/Graphics.hpp>
const float speed = 2;
class Bullet
{
private:
	sf::Vector2f position;
	sf::Vector2f direction;
	float velocity;
	sf::CircleShape shape;

public:
	Bullet(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f direction = sf::Vector2f(0, 0), float velocity = 1.0f);
	~Bullet();

	sf::Vector2f getPos() const;

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;

};

