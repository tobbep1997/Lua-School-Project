#include "GameHandler.h"

GameHandler::GameHandler(lua_State* L, sf::RenderWindow* window)
{
	player = new Player(L);
	
	PushLuaFunctions(L);

	enemyList.push_back(new Enemy(L, 100, 100));
	enemyList.push_back(new Enemy(L, 1, 100));
	wndPtr = window;
	bh = BulletHandler();
	bh.pushToLua(L);
}
	

GameHandler::~GameHandler()
{
	delete player;
	
}

void GameHandler::Update(lua_State* L)
{
	_playerInputHandler(L);
	int error = luaL_loadfile(L, "Lua/GameHandler.lua") ||lua_pcall(L, 0, 0, 0);
	
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		if (enemyList.at(i)->getExploded() == false)
		{
			enemyList.at(i)->Update(L);
		}
	}

	for (size_t i = 0; i < enemyList.size(); i++)
	{
		if (enemyList.at(i)->getExploded())
		{
			sf::CircleShape temp;
			temp.setFillColor(sf::Color(255,0,0,125));
			temp.setRadius(20.0f);
			temp.setPosition(enemyList.at(i)->getPosition());
			deadEnemys.push_back(temp);

			delete enemyList.at(i);
			enemyList.erase(enemyList.begin() + i);
			break;
		}
	}

	/*for (size_t i = 0; i < deadEnemys.size(); i++)
	{
		if (deadEnemys.at(i).getFillColor().a > 10)
		{
			sf::Color temp = deadEnemys.at(i).getFillColor();
			temp.a = temp.a - 0.001f;
			deadEnemys.at(i).setFillColor(temp);
		}
	}*/
	using namespace std::chrono_literals;

	if (m_i == 0)
	{
		m_i++;
		fadeThread = std::async(std::launch::async, &GameHandler::_enemyFade, this);
	}
	auto status = fadeThread.wait_for(0ms);

	if (status == std::future_status::ready) {
		fadeThread.get();
		fadeThread = std::async(std::launch::async, &GameHandler::_enemyFade, this);

	}
	else {
		//std::cout << "Thread running" << std::endl;
	}
	bh.update();
}

void GameHandler::PushLuaFunctions(lua_State * L)
{
	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, GameHandler::luaAddEnemy, 1);
	lua_setglobal(L, "AddEnemy");
}

void GameHandler::AddingEnemy(double posX, double posY)
{
	enemyList.push_back(new Enemy(posX, posY));
}

int GameHandler::luaAddEnemy(lua_State * L)
{
	if (lua_isnumber(L, -1) && lua_isnumber(L, -2))
	{
		GameHandler* p = static_cast<GameHandler*>(lua_touserdata(L, lua_upvalueindex(1)));
		p->AddingEnemy(lua_tonumber(L, -2), lua_tonumber(L, -1));
		lua_pop(L, 2);

		return 0;
	}
	else
	{
		std::cout << "Error: Expected EnemyAddingEnemy(double, double)" << std::endl;
	}
	return 0;
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

	lua_pushinteger(L, sf::Mouse::getPosition(*wndPtr).x);
	lua_setglobal(L, "MouseXX");
	lua_pushinteger(L, sf::Mouse::getPosition(*wndPtr).y);
	lua_setglobal(L, "MouseYY");

	lua_pushboolean(L, false);
	lua_setglobal(L, "SpawnEnemy");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		if (pressed == false)
		{
			//enemyList.push_back(new Enemy(L, 50, 50));
			lua_pushboolean(L, true);
			lua_setglobal(L, "SpawnEnemy");
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
	//target.draw(*enemy);
	bh.draw(target, states);
}

void GameHandler::_enemyFade()
{
	using namespace std::chrono_literals;
	for (size_t i = 0; i < deadEnemys.size(); i++)
	{
		if (deadEnemys.at(i).getFillColor().a > 10)
		{
			std::this_thread::sleep_for(50ms);
			sf::Color temp = deadEnemys.at(i).getFillColor();
			temp.a = temp.a - 1;
			deadEnemys.at(i).setFillColor(temp);
		}
		else
		{
			deadEnemys.erase(deadEnemys.begin() + i);
			break;
		}
	}
}
