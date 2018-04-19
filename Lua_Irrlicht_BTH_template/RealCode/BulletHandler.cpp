#include "BulletHandler.h"



BulletHandler::BulletHandler()
{
}


BulletHandler::~BulletHandler()
{
}

void BulletHandler::update()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
	}
}

void BulletHandler::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->draw(target, state);
	}
}

void BulletHandler::addBullet(sf::Vector2f pos, sf::Vector2f dir)
{
	dir = dir - pos;
	float length = sqrt((dir.x * dir.x) + (dir.y * dir.y));
	if (length != 0)
		dir = sf::Vector2f(dir.x / length, dir.y / length);
	
	bullets.push_back(new Bullet(pos, dir));
}

int BulletHandler::addBullet(lua_State * L)
{
	if (lua_isnumber(L, -1) && lua_isnumber(L, -2) && lua_isnumber(L, -3) && lua_isnumber(L, -4))
	{
		BulletHandler* b = static_cast<BulletHandler*>(lua_touserdata(L, lua_upvalueindex(1)));
		b->addBullet(sf::Vector2f(lua_tonumber(L, -4), lua_tonumber(L, -3)), sf::Vector2f(lua_tonumber(L, -2), lua_tonumber(L, -1)));
		lua_pop(L, 2);
	}
	else
	{
		std::cout << "Error: Expected PlayerSetPos(double, double)" << std::endl;
	}
	return 0;
}

void BulletHandler::pushToLua(lua_State * L)
{
	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, BulletHandler::addBullet, 1);
	lua_setglobal(L, "AddBullet");
}

