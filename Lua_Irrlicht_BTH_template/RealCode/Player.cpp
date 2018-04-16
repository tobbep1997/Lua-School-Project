#include "Player.h"

Player::Player(lua_State * L, const int posX, const int posY)
{
	shape.setRadius(20.0f);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(posX, posY);

	m_health = 100;
	m_attack = 10;
	m_position = sf::Vector2f(posX,posY);

	pushLuaFunctions(L);
}


Player::~Player()
{
}

void Player::Update()
{
}
void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	target.draw(shape);

}

void Player::DamagePlayer(int damage)
{
	m_health -= damage;
}

void Player::GivePlayerHP(int hp)
{
	m_health += hp;
}


int Player::getHealth() const
{
	return m_health;
}

void Player::setHealth(int health)
{
	m_health = health;
}

int Player::getAttack() const
{
	return m_attack;
}

void Player::setAttack(int attack)
{
	m_attack = attack;
}

void Player::move(double x, double y)
{
	shape.setPosition(x, y);
}

int Player::move(lua_State * L)
{
	if (lua_isnumber(L, -1) && lua_isnumber(L, -2))
	{
		Player* p = static_cast<Player*>(lua_touserdata(L, lua_upvalueindex(1)));
		p->move(lua_tonumber(L, -2), lua_tonumber(L, -1));
	}
	return 0;
}

void Player::pushLuaFunctions(lua_State * L)
{
	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Player::move, 1);
	lua_setglobal(L, "MovePlayer");

}


