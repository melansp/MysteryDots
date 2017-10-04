#include "MysteryDots.h"
#include "Utility.h"

Random MysteryDots::rng;

MysteryDots::MysteryDots(std::string title)
	: state(State::READY),
	playArea(0, 0, 800, 560),
	window(sf::VideoMode(800, 600), title),
	bgColor(sf::Color::Black),
	enemyColor(sf::Color::Red),
	initialEnemiesCount(3),
	difficulty(Difficulty::EASY),
	player(new Entity(10.f)),
	hudBg(sf::Vector2f(800, 40)),
	txtTime("Time : 0", font, 25),
	txtBallCount("Ball Count : 0", font, 25),
	txtSpeed("Speed : 0", font, 25),
	txtGameState("", font, 50),
	txtInstructions("", font, 25),
	gameOverSound(gameOverBuffer)
{
	player->shape.setFillColor(sf::Color::Green);
	font.loadFromFile("res/fonts/lazy.ttf");
	hudBg.setFillColor(sf::Color(222,222,222));
	hudBg.setPosition(0, 560);
	txtTime.setPosition(10, 565);
	txtBallCount.setPosition(250, 565);
	txtSpeed.setPosition(550, 565);
	txtTime.setFillColor(sf::Color::Blue);
	txtBallCount.setFillColor(sf::Color::Blue);
	txtSpeed.setFillColor(sf::Color::Blue);
	txtTime.setStyle(sf::Text::Bold);
	txtBallCount.setStyle(sf::Text::Bold);
	txtSpeed.setStyle(sf::Text::Bold);

	txtGameState.setFillColor(sf::Color(177, 177, 177));
	txtGameState.setPosition(200, 100);
	txtGameState.setStyle(sf::Text::Bold);
	
	txtInstructions.setFillColor(sf::Color(177, 177, 177));
	txtInstructions.setPosition(200,200);
	txtInstructions.setStyle(sf::Text::Bold);

	bgMusic.openFromFile("res/music/mainfast.ogg");
	bgMusic.setLoop(true);
	gameOverBuffer.loadFromFile("res/sounds/gameover.ogg");

	resetGame();
}

void MysteryDots::start()
{
	sf::Clock updateTimer;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.F / 60.F);
	while (window.isOpen())
	{
		timeSinceLastUpdate += updateTimer.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void MysteryDots::setBgColor(const sf::Color& color)
{
	bgColor = color;
}

void MysteryDots::setPlayerColor(const sf::Color & color)
{
	player->shape.setFillColor(color);
}

void MysteryDots::setEnemyColor(const sf::Color & color)
{
	enemyColor = color;
}

void MysteryDots::setInitialEnemiesCount(const int & count)
{
	initialEnemiesCount = count;
}

void MysteryDots::setDifficulty(Difficulty aDifficulty)
{
	difficulty = aDifficulty;
}

void MysteryDots::processEvents()
{
	sf::Event evt;
	while (window.pollEvent(evt))
	{
		switch (evt.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::JoystickMoved:
			onJoystickMoved(evt.joystickMove.axis, evt.joystickMove.position);
			break;
		case sf::Event::JoystickButtonPressed:
			if(evt.joystickButton.joystickId == 0)
				onJoystickButtonPressed(evt.joystickButton.button);
			break;
		case sf::Event::JoystickButtonReleased:
			if(evt.joystickButton.joystickId == 0)
				onJoystickButtonReleased(evt.joystickButton.button);
			break;
		default:
			break;
		}
	}
}

void MysteryDots::update(const sf::Time& dt)
{
	if (state == State::PLAYING)
	{
		gameTime += dt;
		moveEntities(dt);
		checkBorderColisions(dt);
		checkPlayerColisions(dt);
		enemySpawnDt += dt;
		if (enemySpawnDt.asSeconds() > 3.f)
		{
			generateEnemy();
			enemySpawnDt = sf::Time::Zero;
		}
	}
	updateHud();
}

void MysteryDots::render()
{
	window.clear(bgColor);
	window.draw(player->shape);
	for (auto enemy : enemies)
	{
		window.draw(enemy->shape);
	}
	window.draw(hudBg);
	window.draw(txtTime);
	window.draw(txtBallCount);
	window.draw(txtSpeed);
	window.draw(txtGameState);
	window.draw(txtInstructions);
	window.display();
}

void MysteryDots::resetGame()
{
	state = State::READY;
	player->shape.setPosition(playArea.width/2, playArea.height/2 + 100);
	enemies.clear();
	enemySpawnDt = sf::Time::Zero;
	gameTime = sf::Time::Zero;
	bgMusic.stop();
	gameOverSound.stop();
	txtGameState.setString("Game Ready");
	txtInstructions.setString("Don't let your dot get hit!\n- A, B, X, Y controls speeds \n- Use gamepad arrows to move \nBegin when ready...");
}

void MysteryDots::startGame()
{
	state = State::PLAYING;
	for (int i = 0; i < initialEnemiesCount; ++i)
	{
		generateEnemy();
	}
	bgMusic.play();
	txtGameState.setString("");
	txtInstructions.setString("");

}

void MysteryDots::stopGame()
{
	state = State::GAME_OVER;
	bgMusic.stop();
	gameOverSound.play();
	txtGameState.setString("Game Over");
	txtInstructions.setString("Press Start to play again.\n\nPress Select to Quit Game.");

}

void MysteryDots::onJoystickMoved(sf::Joystick::Axis axis, float position)
{
	if (state == State::READY)
	{
		startGame();
	}
	if (state == State::PLAYING)
	{
		if (axis == sf::Joystick::X)
		{
			player->velocity.x = position;
		}
		else if (axis == sf::Joystick::Y)
		{
			player->velocity.y = position;
		}
	}
}

void MysteryDots::onJoystickButtonPressed(unsigned int button)
{
	switch (button)
	{
		//A, B, X, Y
	case 0:
	case 1:
	case 2:
	case 3:
		player->speedMultiplier *= (button+2);
		break;
	case 7: //Start
		if (state == State::GAME_OVER)
		{
			resetGame();
		}
		break;
	case 6://Select
		if (state == State::GAME_OVER)
		{
			window.close();
		}
		break;
	}
}

void MysteryDots::onJoystickButtonReleased(unsigned int button)
{
	switch (button)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		player->speedMultiplier /= (button+2);
		break;
	}
}

void MysteryDots::generateEnemy()
{
	Entity::Ptr enemy(new Entity);
	enemy->shape.setFillColor(enemyColor);
	int side = rng(4);
	int directionParity = (rng(2) == 0 ? 1 : -1);
	enemy->velocity.x = 100 * rng(0.8f, 1.2f) * difficulty;
	enemy->velocity.y = 100 * rng(0.8f, 1.2f) * difficulty;
	switch (side)
	{
	case 0://TOP
		enemy->shape.setPosition( player->shape.getRadius() + playArea.left + rng(playArea.width), playArea.top + player->shape.getRadius());
		enemy->velocity.x *= directionParity;
		break;
	case 1://BOTTOM
		enemy->shape.setPosition(player->shape.getRadius() + playArea.left + rng(playArea.width), playArea.top + playArea.height - player->shape.getRadius());
		enemy->velocity.x *= directionParity;
		break;
	case 2://LEFT
		enemy->shape.setPosition(playArea.left + player->shape.getRadius(), playArea.top + rng(playArea.height) + player->shape.getRadius());
		enemy->velocity.y *= directionParity;
		break;
	case 3://RIGHT
		enemy->shape.setPosition(playArea.left + playArea.width - player->shape.getRadius(), playArea.top + rng(playArea.height) + player->shape.getRadius());
		enemy->velocity.y *= directionParity;
		break;
	}
	enemies.push_back(std::move(enemy));
}

void MysteryDots::moveEntities(const sf::Time& dt)
{
	player->shape.move(player->velocity*player->speedMultiplier*dt.asSeconds());
	for (auto enemy : enemies)
	{
		enemy->shape.move(enemy->velocity*enemy->speedMultiplier*dt.asSeconds());
	}
}

void MysteryDots::checkBorderColisions(const sf::Time& dt)
{
	if (player->shape.getPosition().x - player->shape.getRadius() < playArea.left)
	{
		player->shape.setPosition(playArea.left + player->shape.getRadius(), player->shape.getPosition().y);
	}
	if (player->shape.getPosition().y - player->shape.getRadius() < playArea.top)
	{
		player->shape.setPosition(player->shape.getPosition().x, playArea.top + player->shape.getRadius());
	}
	if (player->shape.getPosition().x + player->shape.getRadius() > playArea.left + playArea.width)
	{
		player->shape.setPosition(playArea.left + playArea.width - player->shape.getRadius(), player->shape.getPosition().y);
	}
	if (player->shape.getPosition().y + player->shape.getRadius() > playArea.top + playArea.height)
	{
		player->shape.setPosition(player->shape.getPosition().x, playArea.top + playArea.height - player->shape.getRadius());
	}

	for (auto enemy:enemies)
	{
		if ((enemy->shape.getPosition().x - enemy->shape.getRadius() < playArea.left) ||
			(enemy->shape.getPosition().x + enemy->shape.getRadius() > playArea.left + playArea.width))
		{
			enemy->velocity.x = -enemy->velocity.x;
		}else if ( (enemy->shape.getPosition().y - enemy->shape.getRadius() < playArea.top) ||
			(enemy->shape.getPosition().y + enemy->shape.getRadius() > playArea.top + playArea.height) )
		{
			enemy->velocity.y = -enemy->velocity.y;
		}
	}
}

void MysteryDots::checkPlayerColisions(const sf::Time& dt)
{
	for (auto enemy:enemies)
	{
		if (distance(enemy->shape.getPosition(), player->shape.getPosition()) < enemy->shape.getRadius() + player->shape.getRadius())
		{
			stopGame();
		}
	}
}

void MysteryDots::updateHud()
{
	txtTime.setString("Time : " + std::to_string(static_cast<int>(gameTime.asSeconds())));
	txtBallCount.setString("Ball Count : " + std::to_string(enemies.size()));
	txtSpeed.setString("Speed : " + 
		std::to_string( static_cast<int>(distance(player->velocity, sf::Vector2f())*player->speedMultiplier)));
}
