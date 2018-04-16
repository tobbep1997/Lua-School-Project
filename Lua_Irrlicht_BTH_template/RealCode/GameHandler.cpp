#include "GameHandler.h"

GameHandler::GameHandler()
{
}

GameHandler::~GameHandler()
{
}

void GameHandler::Update(lua_State* L)
{
	_playerInputHandler(L);
	int error = luaL_loadfile(L, "Lua/Jocke.lua") ||lua_pcall(L, 0, 0, 0);
}

void GameHandler::_playerInputHandler(lua_State* L)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		lua_pushstring(L, "A");
		lua_setglobal(L, "KeyBoardState");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		lua_pushstring(L, "D");
		lua_setglobal(L, "KeyBoardState");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		lua_pushstring(L, "W");
		lua_setglobal(L, "KeyBoardState");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		lua_pushstring(L, "S");
		lua_setglobal(L, "KeyBoardState");
	}
	else
	{
		lua_pushstring(L, "FUCK");
		lua_setglobal(L, "KeyBoardState");
	}

}

void GameHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}
