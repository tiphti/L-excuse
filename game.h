#include <SFML/Graphics.hpp>
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
	void handlePlayerInput(bool isPressed);
	void processEvents(Inventaire I);
	void update(sf::Time deltaTime);
	void render(Texte horlogeTxt, Inventaire all_items);
	void gameOver();
	void render(Inventaire I);
private:
	sf::RenderWindow mWindow;
};
