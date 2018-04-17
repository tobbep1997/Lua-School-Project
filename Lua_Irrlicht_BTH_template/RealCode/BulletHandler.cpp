#include "BulletHandler.h"



BulletHandler::BulletHandler()
{
}


BulletHandler::~BulletHandler()
{
}

void BulletHandler::update()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
	}
}

void BulletHandler::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->draw(target, state);
	}
}

void BulletHandler::addBullet(double, double)
{

}
