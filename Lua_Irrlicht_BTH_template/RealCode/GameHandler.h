#pragma once
#include <SFML/Graphics.hpp>
#include "lua.hpp"
#include "Player.h"
#include "Enemy.h"
class GameHandler : public sf::Drawable
{
public:
	GameHandler(lua_State * L = nullptr, sf::RenderWindow * window = nullptr);
	~GameHandler();

	void Update(lua_State* L);

private:

	sf::RenderWindow * wndPtr;

	Player* player;
	Enemy enemy;


	void _playerInputHandler(lua_State* L);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};
