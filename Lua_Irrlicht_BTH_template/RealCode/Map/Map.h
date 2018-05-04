#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML\Graphics\Shape.hpp>
#include <vector>

const unsigned int size = 32;

class Map : public sf::Drawable
{
public:
	Map(sf::Window * Window = nullptr);
	~Map();


	void update();

	void LoadMap();
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	std::vector<sf::RectangleShape*> tiles;
	sf::Color color;

	bool pressed;

	sf::Window * window;
};

