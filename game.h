#include <SFML/Graphics.hpp>
#include "Entity.h"
#pragma once

class Game
{
public:
	Game();
	void run();
private:
	void startingGame();
	void startHorloge();
	void processEvents();
	void Game::update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	sf::RenderWindow mWindow;
	sf::Sprite mPlayer;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;
};
