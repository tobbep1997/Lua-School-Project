#pragma comment(lib, "Irrlicht.lib")
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
//#include <irrlicht.h>
#include <SFML/Graphics.hpp>	
#include "RealCode/Player.h"
#include "RealCode/Enemy.h"
#include "RealCode/GameHandler.h"

void ConsoleThread(lua_State* L) {
	char command[1000];
	while(GetConsoleWindow()) {
		memset(command, 0, 1000);
		std::cin.getline(command, 1000);
		if( luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0) )
			std::cout << lua_tostring(L, -1) << '\n';
	}
}

static int test(lua_State * L)
{
	return 0;
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

	GameHandler gameHandle;

	Player player(L);
	Enemy enemy = Enemy(20,20);
	
	

	int error = luaL_loadfile(L, "Lua/Test.lua") || lua_pcall(L, 0, 0, 0);

	std::thread conThread(ConsoleThread, L);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		gameHandle.Update(L);

		window.clear();
		window.draw(gameHandle);
		window.draw(player);
		window.draw(enemy);
		window.display();
	}

	conThread.join();
	
	return 0;
}