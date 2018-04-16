#pragma once
#include <SFML/Graphics.hpp>
#include "lua.hpp"
class GameHandler : public sf::Drawable
{
public:
	GameHandler();
	~GameHandler();

	void Update(lua_State* L);

private:

	void _playerInputHandler(lua_State* L);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};
