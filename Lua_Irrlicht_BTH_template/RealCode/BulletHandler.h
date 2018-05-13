#pragma once
#include "Bullet.h"
#include <lua.hpp>
#include <iostream>
#include "Enemy.h"
class BulletHandler
{
private:
	std::vector<Bullet*> bullets;

	sf::Vector2u windowSize;

public:
	BulletHandler(const sf::Vector2u & windowSize = sf::Vector2u(0,0));
	~BulletHandler();

	void update(const float deltaTime,std::vector<Enemy*> & enemy);
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void addBullet(sf::Vector2f pos, sf::Vector2f dir);
	static int addBullet(lua_State * L);

	void pushToLua(lua_State * L);
};

