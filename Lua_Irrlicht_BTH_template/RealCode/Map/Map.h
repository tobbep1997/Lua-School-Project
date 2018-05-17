#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML\Graphics\Shape.hpp>
#include <vector>
#include <lua.hpp>
#include "lua.hpp"
#include <fstream>
const unsigned int size = 32;



class Map : public sf::Drawable
{
public:
	Map(sf::Window * Window = nullptr, lua_State * L = nullptr);
	~Map();


	void update();

	static int L_Map(lua_State * L);
	static int S_Map(lua_State * L);

	void LoadMap();
	void SaveMap();
	void clearMap();
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setColor(double r, double g, double b, double a);
	static int setColor(lua_State * L);

	std::vector<sf::RectangleShape*> & getTiles();
private:
	std::vector<sf::RectangleShape*> tiles;
	sf::Color color;

	void pushLuaFunc();

	bool pressed;

	sf::Window * window;

	lua_State * L;
};

