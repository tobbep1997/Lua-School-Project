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
	clearMap();
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


	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && !pressed) {
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

	//if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		pressed = false;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && !pressed) {

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		SaveMap();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		LoadMap();
}

int Map::L_Map(lua_State * L)
{
	Map* m = static_cast<Map*>(lua_touserdata(L, lua_upvalueindex(1)));
	m->LoadMap();
	return 0;
}

int Map::S_Map(lua_State * L)
{
	Map* m = static_cast<Map*>(lua_touserdata(L, lua_upvalueindex(1)));
	m->SaveMap();
	return 0;
}

void Map::LoadMap()
{
	std::ifstream in;
	in.open("Map.txt");
	this->clearMap();

	int vSize;
	sf::Vector2i pos;
	int r, b, g, a;
	in >> vSize;
	for (int i = 0; i < vSize; i++)
	{
		in >> pos.x;
		in >> pos.y;
		in >> r;
		in >> g;
		in >> b;
		in >> a;

		sf::RectangleShape * s = new sf::RectangleShape();
		s->setPosition(pos.x, pos.y);
		s->setSize(sf::Vector2f(size, size));
		s->setFillColor(sf::Color(r,g,b,a));
		tiles.push_back(s);
	}
}

void Map::SaveMap()
{
	std::ofstream o;
	o.open("Map.txt");
	o << tiles.size() << std::endl;
	for (auto & t : tiles)
	{
		o << t->getPosition().x << std::endl;
		o << t->getPosition().y << std::endl;

		o << static_cast<int>(t->getFillColor().r) << std::endl;
		o << static_cast<int>(t->getFillColor().g) << std::endl;
		o << static_cast<int>(t->getFillColor().b) << std::endl;
		o << static_cast<int>(t->getFillColor().a) << std::endl;
	}
	o.close();


}

void Map::clearMap()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		delete tiles[i];
	}
	tiles.clear();
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

	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Map::L_Map, 1);
	lua_setglobal(L, "loadMap");

	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Map::S_Map, 1);
	lua_setglobal(L, "saveMap");
}
