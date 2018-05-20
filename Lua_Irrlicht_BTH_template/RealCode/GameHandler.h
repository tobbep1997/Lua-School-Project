#pragma once
#include <SFML/Graphics.hpp>
#include "lua.hpp"
#include "Player.h"
#include "Enemy.h"
#include <future>
#include "BulletHandler.h"
#include "Map\Map.h"
class GameHandler : public sf::Drawable
{
public:
	GameHandler(lua_State * L = nullptr, sf::RenderWindow * window = nullptr, Map * map = nullptr);
	~GameHandler();

	void Update(lua_State* L, const float deltaTime);

	bool getAlive();

	void setHighScore(int highScore);

private:
	void PushLuaFunctions(lua_State * L);

	void AddingEnemy(double posX, double posY);
	static int luaAddEnemy(lua_State * L);
	void _playerInputHandler(lua_State* L);

	static int random(lua_State * L);

	static int luaSetTextBullet(lua_State * L);
	void SetBulletText(int bullets, int hp);

	static int luaSetTextScore(lua_State * L);
	void SetScoreText(int amount);

	Player* player;
	BulletHandler bh;
	Enemy* enemy;

	Map * m_map;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//void _playerInputHandler(lua_State* L);
	void _enemyFade();
	int m_i = 0;
	std::future<void> fadeThread;

	sf::RenderWindow * wndPtr;
	//Player* player;
	/*Enemy* enemy;
	Enemy* enemy2;*/
	std::vector<Enemy*> enemyList;
	std::vector<sf::CircleShape> deadEnemys;

	int score = 0;
	int highScore = 0;

	bool pressed = false;

	bool keepAlive = true;
	bool firstTime = true;

	sf::Font font;
	sf::Text text;
	sf::Text hpText;
	sf::Text scoreText;
	sf::Text deadText;
	sf::Text highScoreText;
};
