#include <SFML/Graphics.hpp>
#include "timer.h"
#pragma once

class Game
{
public:
	Game();
	void menuChoice();
private:
	void run();
	void introGame();
	void drawClock(sf::Text text, sf::Font font, Timer timer, int minutes);
	void processEvents();
	void handlePlayerInput(bool isPressed);
	//void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void update(sf::Time deltaTime);
	void render();
	void gameOver();
private:
	enum State { running, sommaire };
	State mState;
	sf::RenderWindow mWindow;
	sf::Sprite mPlayer;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;
};
