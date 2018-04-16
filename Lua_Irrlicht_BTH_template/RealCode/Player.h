#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
public:
	Player();
	~Player();
	
	void Update();

	void DamagePlayer(int damage);
	void GivePlayerHP(int hp);

	int getHealth() const;
	void setHealth(int health);

	int getAttack() const;
	void setAttack(int attack);

private:
	
	int m_health;
	int m_attack;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::CircleShape shape;
	

};

