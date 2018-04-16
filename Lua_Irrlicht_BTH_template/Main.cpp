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
#include <irrlicht.h>
#include <SFML/Graphics.hpp>	
#include "RealCode/Player.h"
#include "RealCode/Enemy.h"

void ConsoleThread(lua_State* L) {
	char command[1000];
	while(GetConsoleWindow()) {
		memset(command, 0, 1000);
		std::cin.getline(command, 1000);
		if( luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0) )
			std::cout << lua_tostring(L, -1) << '\n';
	}
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	Player player;
	Enemy enemy = Enemy(20,20);

	int error = luaL_loadfile(L, "../Lua/Test.lua") || lua_pcall(L, 0, 0, 0);

	std::cout << error << std::endl;

	std::thread conThread(ConsoleThread, L);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(player);
		window.draw(enemy);
		window.display();
	}

	conThread.join();
	/*

	irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(640, 480), 16, false, false, true, 0);
	if(!device)
		return 1;

	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
	irr::video::IVideoDriver* driver	= device->getVideoDriver();
	irr::scene::ISceneManager* smgr		= device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv	= device->getGUIEnvironment();

	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", irr::core::rect<irr::s32>(10, 10, 260, 22), true);

	while(device->run()) {
		driver->beginScene(true, true, irr::video::SColor(255, 90, 101, 140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();		
	}

	device->drop();

	*/
	return 0;
}