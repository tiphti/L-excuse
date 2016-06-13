#include <SFML/Graphics.hpp>
#include "timer.h"
#include "entity.h"
#pragma once

class Game
{
public:
	Game();
	void menuChoice();
private:
	void run();
	void introGame();
	//void drawClock(sf::Text text, sf::Font font, Timer timer, int minutes);
	void processEvents(Inventaire I);
	void handlePlayerInput(bool isPressed);
	void update(sf::Time deltaTime);
	void render(Texte horlogeTxt, Inventaire I);
	void gameOver();
private:
	sf::RenderWindow mWindow;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;
};
