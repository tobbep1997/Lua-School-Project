#pragma once
#include <SFML/Graphics.hpp>
#include "lua.hpp"
#include "Player.h"
#include "Enemy.h"
#include <future>
#include "BulletHandler.h"
class GameHandler : public sf::Drawable
{
public:
	GameHandler(lua_State * L = nullptr, sf::RenderWindow * window = nullptr);
	~GameHandler();

	void Update(lua_State* L);

private:
	void PushLuaFunctions(lua_State * L);

	void AddingEnemy(double posX, double posY);
	static int luaAddEnemy(lua_State * L);
	void _playerInputHandler(lua_State* L);

	Player* player;
	BulletHandler bh;
	Enemy* enemy;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//void _playerInputHandler(lua_State* L);
	void _enemyFade();
	int m_i = 0;
	std::future<void> fadeThread;

	sf::RenderWindow * wndPtr;
	//Player* player;
	/*Enemy* enemy;
	Enemy* enemy2;*/
	std::vector<Enemy*> enemyList;
	std::vector<sf::CircleShape> deadEnemys;

	bool pressed = false;
};
