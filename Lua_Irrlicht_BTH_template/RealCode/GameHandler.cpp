#include "GameHandler.h"

GameHandler::GameHandler(lua_State* L, sf::RenderWindow* window)
{
	player = new Player(L);
	
	enemy = new Enemy(L, 100,100);
	enemy2 = new Enemy(L, 1, 100);
	wndPtr = window;
}
	

GameHandler::~GameHandler()
{
	delete player;
	delete enemy;
	delete enemy2;
}

void GameHandler::Update(lua_State* L)
{
	_playerInputHandler(L);
	int error = luaL_loadfile(L, "Lua/Jocke.lua") ||lua_pcall(L, 0, 0, 0);
	enemy->Update(L);
	enemy2->Update(L);
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		lua_pushinteger(L, sf::Mouse::getPosition(*wndPtr).x);
		lua_setglobal(L, "MouseX");
		lua_pushinteger(L, sf::Mouse::getPosition(*wndPtr).y);
		lua_setglobal(L, "MouseY");
	}
	else
	{
		lua_pushinteger(L, -1);
		lua_setglobal(L, "MouseX");
		lua_pushinteger(L, -1);
		lua_setglobal(L, "MouseY");
	}

}

void GameHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*player);
	target.draw(*enemy);
	target.draw(*enemy2);
}
