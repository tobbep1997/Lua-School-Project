#pragma once
#include "Bullet.h"
#include <lua.hpp>
#include <iostream>
class BulletHandler
{
private:
	std::vector<Bullet*> bullets;

public:
	BulletHandler();
	~BulletHandler();

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void addBullet(sf::Vector2f pos, sf::Vector2f dir);
	static int addBullet(lua_State * L);

	void pushToLua(lua_State * L);
};

