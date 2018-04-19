#include "Enemy.h"
#include <iostream>
#include <complex>


Enemy::Enemy(lua_State * L,const int posX , const int posY)
{
	shape.setPosition(posX, posY);
	shape.setRadius(20.0f);
	shape.setFillColor(sf::Color::Red);

	m_health = 100;
	m_attack = 10;
	m_position = sf::Vector2f(posX, posY);

	pushLuaFunctions(L);
}

Enemy::Enemy()
{
	std::cout << "NAI BLYET NOT USE THE FUNCTION" << std::endl;
}


Enemy::~Enemy()
{
}

void Enemy::Update(lua_State * L)
{
	lua_pushinteger(L, m_position.x);
	lua_setglobal(L, "LocalEnemyPosX");
	lua_pushinteger(L, m_position.y);
	lua_setglobal(L, "LocalEnemyPosY");
	
	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Enemy::luaMoveTowards, 1);
	lua_setglobal(L, "EnemyMoveTowards");

	int error =  luaL_loadfile(L, "Lua/EnemyAI.lua") || lua_pcall(L, 0, 0, 0);
	
	if (error)
	{
		std::cout << lua_tostring(L, -1) << '\n';
		lua_pop(L, 1);
	}
	//DIE LUA DIEEEEE
	/*lua_pushnumber(L, 0);
	lua_setglobal(L, "LocalEnemyPosX");
	lua_pushnumber(L, 0);
	lua_setglobal(L, "LocalEnemyPosY");*/
}

void Enemy::DamageEnemy(int damage)
{
	m_health -= damage;
}

int Enemy::getHealth()
{
	return m_health;
}

void Enemy::setHealth(int health)
{
	m_health = health;
}

int Enemy::getAttack()
{
	return m_attack;
}

void Enemy::setAttack(int attack)
{
	m_attack = attack;
}

sf::Vector2f Enemy::getPosition() const 
{
	return m_position;
}

sf::Vector2f Enemy::_normalize(sf::Vector2f pos)
{
	float lenght = std::sqrt(std::pow(pos.x, 2) + std::pow(pos.y, 2));

	if (lenght == 0)
	{
		return sf::Vector2f(0, 0);
	}

	return sf::Vector2f(pos.x / lenght, pos.y / lenght);
}

void Enemy::MoveTowards(double speed, double posx1, double posy1, double posx2, double posy2)
{
	sf::Vector2f dir = _normalize(sf::Vector2f(posx1 -posx2,posy1 - posy2));
	
	shape.move((float)speed * dir);
	m_position = shape.getPosition();
}

double Enemy::getLenghtTo(double posx1, double posy1, double posx2, double posy2)
{
	sf::Vector2f lenght = sf::Vector2f(posx1 - posx2, posy1 - posy2);

	return std::sqrt(std::pow(lenght.x, 2) + std::pow(lenght.y, 2));
}


void Enemy::pushLuaFunctions(lua_State * L)
{
	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Enemy::luaGetThisPos, 1);
	lua_setglobal(L, "EnemyGetPos");

	

	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Enemy::luaGetThisAttack, 1);
	lua_setglobal(L, "EnemyGetAttack");

	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Enemy::luaGetLenghtTo, 1);
	lua_setglobal(L, "EnemyGetLenghtTo");  
}

int Enemy::luaGetThisPos(lua_State * L)
{
	Enemy* p = static_cast<Enemy*>(lua_touserdata(L, lua_upvalueindex(1)));
	lua_pushinteger(L, p->getPosition().x);
	lua_pushinteger(L, p->getPosition().y);
	return 2;
}

int Enemy::luaGetThisAttack(lua_State * L)
{
	Enemy* p = static_cast<Enemy*>(lua_touserdata(L, lua_upvalueindex(1)));
	lua_pushinteger(L, p->getAttack());
	return 1;
}

int Enemy::luaMoveTowards(lua_State * L)
{
	if (lua_isnumber(L, -1) && lua_isnumber(L, -2) && lua_isnumber(L, -3) && lua_isnumber(L, -4) && lua_isnumber(L, -5))
	{
		Enemy* p = static_cast<Enemy*>(lua_touserdata(L, lua_upvalueindex(1)));
		p->MoveTowards(lua_tonumber(L, -5), lua_tonumber(L, -4), lua_tonumber(L, -3), lua_tonumber(L, -2), lua_tonumber(L, -1));
		lua_pop(L, 5);
	}
	else
	{
		std::cout << "Error: Expected EnemyMoveTowards(double, double, double, double, double)" << std::endl;
	}
	return 0;
}

int Enemy::luaGetLenghtTo(lua_State * L)
{
	if (lua_isnumber(L, -1) && lua_isnumber(L, -2) && lua_isnumber(L, -3) && lua_isnumber(L, -4))
	{
		Enemy* p = static_cast<Enemy*>(lua_touserdata(L, lua_upvalueindex(1)));
		double lenght =  p->getLenghtTo( lua_tonumber(L, -4), lua_tonumber(L, -3), lua_tonumber(L, -2), lua_tonumber(L, -1));
		lua_pop(L, 4);
		lua_pushnumber(L, lenght);
		//lua_pushinteger(L, p->getAttack());
		return 1;
	}
	else
	{
		std::cout << "Error: Expected EnemyMoveTowards(double, double, double, double, double)" << std::endl;
	}
	return 0;
}

void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}

