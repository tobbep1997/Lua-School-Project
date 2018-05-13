#include "Map.h"



Map::Map(sf::Window * Window, lua_State * L)
{
	this->window = Window;
	pressed = false;
	color = sf::Color(255, 255, 0, 255);
	this->L = L;
	pushLuaFunc();
}

Map::~Map()
{
}
#include <iostream>
void Map::update()
{
	int error = luaL_loadfile(L, "Lua/Editor.lua") || lua_pcall(L, 0, 0, 0);
	if (error)
	{
		std::cout << lua_tostring(L, -1) << '\n';
		lua_pop(L, 1);
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

		pressed = true;

		mousePos.x = ((mousePos.x + size / 2) / size) * size;
		mousePos.y = ((mousePos.y + size / 2) / size) * size;

		//std::cout << mousePos.x << "	" << mousePos.y << std::endl;
		bool add = true;
		for (int i = 0; i < tiles.size(); i++)
		{
			if (tiles[i]->getPosition() == sf::Vector2f(mousePos))
			{
				add = false;
			}
		}
		if (add)
		{
			sf::RectangleShape * s = new sf::RectangleShape();
			s->setPosition(mousePos.x, mousePos.y);
			s->setSize(sf::Vector2f(size, size));
			s->setFillColor(color);
			tiles.push_back(s);
		}
		//result = ((number + multiple / 2) / multiple) * multiple;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		pressed = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

		mousePos.x = ((mousePos.x + size / 2) / size) * size;
		mousePos.y = ((mousePos.y + size / 2) / size) * size;

		for (int i = 0; i < tiles.size(); i++)
		{
			if (tiles[i]->getPosition() == sf::Vector2f(mousePos))
			{
				tiles.erase(tiles.begin() + i);
			}
		}
	}

}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//std::cout << "s";
	for (size_t i = 0; i < tiles.size(); i++)
	{
		target.draw(*tiles[i]);
	}
}


void Map::setColor(double r, double g, double b, double a)
{
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = a;
}

int Map::setColor(lua_State * L)
{
	if (lua_isnumber(L, -1) && lua_isnumber(L, -2) && lua_isnumber(L, -3) && lua_isnumber(L, -4))
	{
		Map* b = static_cast<Map*>(lua_touserdata(L, lua_upvalueindex(1)));
		b->setColor(lua_tonumber(L, -4), lua_tonumber(L, -3), lua_tonumber(L, -2), lua_tonumber(L, -1));
		lua_pop(L, 4);
	}
	else
	{
		std::cout << "Error: Expected setColor(double, double, double, double)" << std::endl;
	}
	return 0;
}

std::vector<sf::RectangleShape*>& Map::getTiles()
{
	return tiles;
}

void Map::pushLuaFunc()
{
	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Map::setColor, 1);
	lua_setglobal(L, "setColor");
}
