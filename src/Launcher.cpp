#include "MysteryDots.h"

int main()
{
	MysteryDots game("Myster Dots");
	game.setBgColor(sf::Color::Black);
	game.setPlayerColor(sf::Color::Green);
	game.setEnemyColor(sf::Color::Red);
	game.setInitialEnemiesCount(5);
	game.setDifficulty(MysteryDots::MEDIUM);
	game.start();
}