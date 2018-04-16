#pragma once
#include <SFML/Graphics.hpp>


class Enemy : public sf::Drawable
{
public:
	Enemy(const int posX = 0, const int posY = 0);
	~Enemy();
	
	void Update();

	void DamageEnemy(int damage);

	int getHealth();
	void setHealth(int health);

	int getAttack();
	void setAttack(int attack);

private:
	int m_health;
	int m_attack;
	sf::Vector2f m_position;

	sf::CircleShape shape;

	

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	
};
