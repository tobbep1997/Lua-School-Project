#pragma once
#include <SFML/Graphics.hpp>
#include "lua.hpp"

class Enemy : public sf::Drawable
{
public:
	Enemy(lua_State * L, const int posX = 0, const int posY = 0);
	Enemy(const int posX = 0, const int posY = 0);
	Enemy();
	~Enemy();
	
	void Update(lua_State * L);

	void DamageEnemy(int damage);

	int getHealth();
	void setHealth(int health);

	int getAttack();
	void setAttack(int attack);

	bool getExploded();
	void setExploded(bool state);

	sf::Vector2f getPosition() const;

	void MoveTowards(double speed, double posx1, double posy1, double posx2, double posy2);

	double getLenghtTo(double posx1, double posy1, double posx2, double posy2);

	void pushLuaFunctions(lua_State * L);

	//-------------------------- LUA||
	static int luaGetThisPos(lua_State * L);
	static int luaGetThisAttack(lua_State * L);
	static int luaMoveTowards(lua_State * L);
	static int luaGetLenghtTo(lua_State * L);

	static int luaGetExploded(lua_State * L);
	static int luaSetExploded(lua_State * L);
	

private:
	sf::Vector2f _normalize(sf::Vector2f pos);

	int m_health;
	int m_attack;

	bool m_exploded = false;

	sf::Vector2f m_position;

	sf::CircleShape shape;

	

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	
};
