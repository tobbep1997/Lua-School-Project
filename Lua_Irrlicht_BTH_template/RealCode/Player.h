#pragma once
#ifdef _DEBUG
#pragma comment(lib, "LuaLibd.lib")
#else
#pragma comment(lib, "Lualib.lib")
#endif

#include <lua.hpp>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "lua.hpp"
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
public:
	Player(lua_State * L, const int posX = 0, const int posY = 0);
	Player();
	~Player();
	
	void Update();

	void DamagePlayer(int damage);
	void GivePlayerHP(int hp);

	int getHealth() const;
	void setHealth(int health);

	int getAttack() const;
	void setAttack(int attack);

	sf::Vector2f getPlayerPosition() const;
	void setPlayerPosition(double, double);


	//-----------------------------------	LUA

	static int move(lua_State * L);
	static int setHealth(lua_State * L);

	void pushPlayerHealth(lua_State * L);
	static int getPlayerHealth(lua_State * l);
	static int getPlayerPos(lua_State * l);

	static int setPlayerPos(lua_State* L);
	static int luaDamagePlayer(lua_State* L);

private:

	void pushLuaFunctions(lua_State * L);
	void move(double x, double y);
	
	int m_health;
	int m_attack;
	sf::Vector2f m_position;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::CircleShape shape;
	

};

