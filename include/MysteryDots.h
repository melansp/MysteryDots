#ifndef _MYSTERY_DOTS_H_
#define _MYSTERY_DOTS_H_

#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Entity.h"
#include "Random.h"

class MysteryDots
{
public:
	enum Difficulty { EASY = 1, MEDIUM = 2, HARD = 3};

	MysteryDots(std::string title);
	MysteryDots() = delete;
	MysteryDots(const MysteryDots&) = delete;
	MysteryDots& operator=(const MysteryDots&) = delete;

	void start();

	void setBgColor(const sf::Color& color);
	void setPlayerColor(const sf::Color& color);
	void setEnemyColor(const sf::Color& color);
	void setInitialEnemiesCount(const int& count);
	void setDifficulty(Difficulty aDifficulty);

private:
	enum class State { READY, PLAYING, GAME_OVER } state;
	static Random rng;
	void processEvents();
	void update(const sf::Time& dt);
	void render();

	void resetGame();
	void startGame();
	void stopGame();

	void onJoystickMoved(sf::Joystick::Axis axis, float position);
	void onJoystickButtonPressed(unsigned int button);
	void onJoystickButtonReleased(unsigned int button);

	void generateEnemy();
	void moveEntities(const sf::Time& dt);
	void checkBorderColisions(const sf::Time& dt);
	void checkPlayerColisions(const sf::Time& dt);
	void updateHud();

	sf::FloatRect playArea;
	sf::RenderWindow window;

	//configurables
	sf::Color bgColor;
	sf::Color enemyColor;
	int initialEnemiesCount;
	Difficulty difficulty;

	//Game entities
	Entity::Ptr player;
	std::list<Entity::Ptr> enemies;
	sf::Time enemySpawnDt;
	sf::Time gameTime;

	//HUD
	sf::RectangleShape hudBg;
	sf::Font font;
	sf::Text txtTime;
	sf::Text txtBallCount;
	sf::Text txtSpeed;

	//Instructions & Menu
	sf::Text txtGameState;
	sf::Text txtInstructions;

	//music and sound
	sf::Music bgMusic;
	sf::SoundBuffer gameOverBuffer;
	sf::Sound gameOverSound;

};

#endif