#include "GameHandler.h"

GameHandler::GameHandler(lua_State* L, sf::RenderWindow* window)
{
	player = new Player(L);
	
	

	enemyList.push_back(new Enemy(L, 100, 100));
	enemyList.push_back(new Enemy(L, 1, 100));
	wndPtr = window;
}
	

GameHandler::~GameHandler()
{
	delete player;
	
}

void GameHandler::Update(lua_State* L)
{
	_playerInputHandler(L);
	int error = luaL_loadfile(L, "Lua/Jocke.lua") ||lua_pcall(L, 0, 0, 0);
	
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		if (enemyList.at(i)->getExploded() == false)
		{
			enemyList.at(i)->Update(L);
		}
	}

	std::cout << enemyList.size() << std::endl;
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		if (enemyList.at(i)->getExploded())
		{
			delete enemyList.at(i);
			enemyList.erase(enemyList.begin() + i);
			break;
		}
	}
	
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		if (pressed == false)
		{
			enemyList.push_back(new Enemy(L, 50, 50));
			pressed = true;
		}
	}
	else
	{
		pressed = false;
	}

}

void GameHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*player);

	for (size_t i = 0; i < enemyList.size(); i++)
	{
		target.draw(*enemyList.at(i));
	}
}
