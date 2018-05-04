#include "Map.h"



Map::Map(sf::Window * Window)
{
	this->window = Window;
	pressed = false;
	color = sf::Color(255, 255, 0, 255);
}

Map::~Map()
{
}
#include <iostream>
void Map::update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

		pressed = true;

		mousePos.x = ((mousePos.x + size / 2) / size) * size;
		mousePos.y = ((mousePos.y + size / 2) / size) * size;

		//std::cout << mousePos.x << "	" << mousePos.y << std::endl;
		sf::RectangleShape * s = new sf::RectangleShape();
		s->setPosition(mousePos.x, mousePos.y);
		s->setSize(sf::Vector2f(size, size));
		s->setFillColor(color);
		
		tiles.push_back(s);

		//result = ((number + multiple / 2) / multiple) * multiple;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		pressed = false;
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//std::cout << "s";
	for (size_t i = 0; i < tiles.size(); i++)
	{
		target.draw(*tiles[i]);
	}
}
