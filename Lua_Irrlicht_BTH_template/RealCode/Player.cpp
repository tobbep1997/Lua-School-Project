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

Player::Player()
{
	std::cout << "DONT USE THIS PEZSE\n";
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

sf::Vector2f Player::getPlayerPosition() const
{
	return this->m_position;
}

void Player::setPlayerPosition(double x, double y)
{
	this->m_position.x = x;
	this->m_position.y = y;
}

void Player::move(double x, double y)
{
	m_position.x += x;
	m_position.y += y;
	shape.setPosition(m_position);
}

int Player::move(lua_State * L)
{
	if (lua_isnumber(L, -1) && lua_isnumber(L, -2))
	{
		Player* p = static_cast<Player*>(lua_touserdata(L, lua_upvalueindex(1)));
		p->move(lua_tonumber(L, -2), lua_tonumber(L, -1));
	}
	else
	{
		std::cout << "Error: Expected MovePlayer(double, double)" << std::endl;
	}
	return 0;
}

int Player::setHealth(lua_State * L)
{
	if (lua_isnumber(L, -1))
	{
		Player* p = static_cast<Player*>(lua_touserdata(L, lua_upvalueindex(1)));
		p->setHealth(lua_tointeger(L, -1));
	}
	else
	{
		std::cout << "Error: Expected PlayerSetHealth(int)" << std::endl;
	}	
	return 0;
}

void Player::pushPlayerHealth(lua_State * L)
{
	lua_pushinteger(L, m_health);
}

int Player::getPlayerHealth(lua_State * L)
{
	Player* p = static_cast<Player*>(lua_touserdata(L, lua_upvalueindex(1)));
	p->pushPlayerHealth(L);
	return 1;
}

int Player::getPlayerPos(lua_State * L)
{
	Player* p = static_cast<Player*>(lua_touserdata(L, lua_upvalueindex(1)));
	lua_pushinteger(L, p->getPlayerPosition().x);
	lua_pushinteger(L, p->getPlayerPosition().y);
	return 2;	
}

int Player::setPlayerPos(lua_State * L)
{
	if (lua_isnumber(L, -1) && lua_isnumber(L, -2))
	{
		Player* p = static_cast<Player*>(lua_touserdata(L, lua_upvalueindex(1)));
		p->setPlayerPosition(lua_tonumber(L, -2), lua_tonumber(L, -1));
		lua_pop(L, 2);
	}
	else
	{
		std::cout << "Error: Expected PlayerSetPos(double, double)" << std::endl;
	}
	return 0;
}

void Player::pushLuaFunctions(lua_State * L)
{
	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Player::move, 1);
	lua_setglobal(L, "PlayerMove");
	
	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Player::getPlayerHealth, 1);
	lua_setglobal(L, "PlayerGetHealth");

	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Player::setHealth, 1);
	lua_setglobal(L, "PlayerSetHealth");

	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Player::getPlayerPos, 1);
	lua_setglobal(L, "PlayerGetPos");

	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, Player::setPlayerPos, 1);
	lua_setglobal(L, "PlayerSetPos");
}


