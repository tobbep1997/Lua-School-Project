#pragma once
#include "Bullet.h"
class BulletHandler
{
private:
	std::vector<Bullet*> bullets;

public:
	BulletHandler();
	~BulletHandler();

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void addBullet(double, double);
};

