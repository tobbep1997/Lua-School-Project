#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML\Graphics\Shape.hpp>
#include <vector>
#include <lua.hpp>
#include "lua.hpp"
const unsigned int size = 32;

class Map : public sf::Drawable
{
public:
	Map(sf::Window * Window = nullptr, lua_State * L = nullptr);
	~Map();


	void update();

	void LoadMap();
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setColor(double r, double g, double b, double a);
	static int setColor(lua_State * L);
private:
	std::vector<sf::RectangleShape*> tiles;
	sf::Color color;

	void pushLuaFunc();

	bool pressed;

	sf::Window * window;

	lua_State * L;
};

