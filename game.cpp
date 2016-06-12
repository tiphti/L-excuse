#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <windows.h> //Sleep
#include <iostream>
#include <stdlib.h>
#include "game.h"
#include "timer.h"
#include "entity.h"

using namespace sf;
using namespace std;

#pragma region variables
const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
const float PlayerSpeed = 100.f;
const int FONT_SIZE = 80;
const int WIDTH = 800; //largeur de la fenetre
const int HEIGHT = 600; //hauteur de la fenetre
const float START_TIME = 7.0f;
std::string const red = "red";
std::string const white = "white";
std::string const pink = "pink";
std::string const black = "black";
#pragma endregion variables

template <class T> string convertitNbEnString(T nb)
/* Ce template permet de convertir un nombre (float, int, double) en string */
{
	ostringstream s;
	s << nb;
	return s.str();
}

Game::Game() :
	mWindow(sf::VideoMode(WIDTH, HEIGHT, 32), "super jeu trop cool")
{
	mWindow.setFramerateLimit(60);
	//mPlayer.setPosition(100.f, 100.f);
}

void Game::menuChoice()
{
	Texture texture1, texture2;
	if (!texture1.loadFromFile("play.png"))
	{
		cerr << "erreur de chargement de l'image 'play.png'" << endl;
	}
	if (!texture2.loadFromFile("quit.png"))
	{
		cerr << "erreur de chargement de l'image 'play.png'" << endl;
	}
	Sprite play(texture1);
	Sprite quit(texture2);
	play.setPosition(200.f, 50.f);
	quit.setPosition(200.f, 325.f);
	FloatRect rect1 = play.getGlobalBounds();
	FloatRect rect2 = quit.getGlobalBounds();
	// A SUPPRIMER
#pragma region variables2
	float largeur = rect1.width;//385 c'est un FLOAT
	float hauteur = rect1.height;//250
	float pos_x = rect1.left;//200
	float pos_y = rect1.top;//100
	float largeur2 = rect2.width;//385
	float hauteur2 = rect2.height;//250
	float pos_x2 = rect2.left;//200
	float pos_y2 = rect2.top;//300
	int mouse_x = Mouse::getPosition().x; // c'est un INT
	int mouse_y = Mouse::getPosition().y;
	int window_x = mWindow.getPosition().x;
	int window_y = mWindow.getPosition().y;
#pragma endregion variables2
	// FIN DE 'A SUPPRIMER'
	do
	{
		// affichage du menu
		mWindow.clear();
		mWindow.draw(play);
		mWindow.draw(quit);
		mWindow.display();
		// gestion des evenements sur le menu
		Event event;
		while (mWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				mWindow.close();
				break;
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if ((rect1.left <= (Mouse::getPosition().x - mWindow.getPosition().x))
						&& ((Mouse::getPosition().x - mWindow.getPosition().x) <= (rect1.left + rect1.width))
						&& (rect1.top <= (Mouse::getPosition().y - mWindow.getPosition().y))
						&& ((Mouse::getPosition().y - mWindow.getPosition().y) <= (rect1.top + rect1.height)))
					{
						cout << "click on play ok" << endl;
						run();
					}
					else if ((rect2.left <= (Mouse::getPosition().x - mWindow.getPosition().x))
						&& ((Mouse::getPosition().x - mWindow.getPosition().x) <= (rect2.left + rect2.width))
						&& (rect2.top <= (Mouse::getPosition().y - mWindow.getPosition().y))
						&& ((Mouse::getPosition().y - mWindow.getPosition().y) <= (rect2.top + rect2.height)))
					{
						cout << "click on quit ok" << endl;
						mWindow.close();
					}
					else { cout << "missed, are you dumb ?" << endl; }
					break;
				}
			}
			default:
				break;
			}
		}
	} while (1);
}

void Game::run()
{
	//sf::Clock clock;
	//sf::Time timeSinceLastUpdate = sf::Time::Zero;
	/* DEBUT configuration de l'horloge affichee dans le jeu */
	Timer secondes;
	Text text;
	Font font;
	int minutes = 6; // il est 6h dans le jeu lorsque le personnage se reveil
	text.setStyle(Text::Bold);
	if (!font.loadFromFile("digital-7.ttf"))
	{
		cerr << "Erreur durant le chargement de la fonte" << endl;
	}
	/* FIN config de l'horloge affichee dans le jeu */
	introGame();
	secondes.Start(); // mise en marche de l'horloge
	while (mWindow.isOpen())
	{
		drawClock(text, font, secondes, minutes);
		if (convertitNbEnString((int)secondes.GetTime()) == "60")
		{
			++minutes;
			secondes.Reinitialize();
			secondes.Start();
		}
		processEvents();
		/*
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
		timeSinceLastUpdate -= TimePerFrame;
		processEvents();
		update(TimePerFrame);
		}*/
		//render();
		if (convertitNbEnString((int)secondes.GetTime()) == "50")
		{
			secondes.Pause();
			gameOver();
		}
	}
}

void Game::introGame()
{
	cout << "debut starting game" << endl;
	mState = running;
	Font font;
	Text zzz;
	if (!font.loadFromFile("bboron.ttf"))
	{
		cerr << "Erreur durant le chargement de la fonte" << endl;
	}
	Texte mText(zzz, font, "zzz", 100, white);
	mText.setPosition(WIDTH / 2, HEIGHT / 2);
	mWindow.clear();
	mText.draw(mWindow);
	mWindow.display();
	Sleep(1000); // pause de 3s
	cout << "fin starting game" << endl;
}

void Game::drawClock(sf::Text text, sf::Font font, Timer timer, int minutes)
{
	string minutesString = convertitNbEnString((int)minutes);
	string secondesString = convertitNbEnString((int)timer.GetTime());
	Texte horlogeString(text, font, minutesString + "h: " + secondesString + "min", 30, white);
	mWindow.clear();
	horlogeString.draw(mWindow);
	mWindow.display();
}

//void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
void Game::handlePlayerInput(bool isPressed)
{
	/*
	if (key == sf::Keyboard::Z)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::Q)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;*/
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				handlePlayerInput(true);
				break;
			}
		}
		case Event::MouseButtonReleased:
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				handlePlayerInput(false);
				break;
			}
		}
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;
	//mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
	//Personnage mPlayer("mPlayer");
	//Personnage maman("maman");
	//Personnage chat("chat");
	mWindow.clear();
	//mPlayer.drawPerso(mWindow);
	//maman.drawPerso(mWindow);
	//mSprite.draw(mWindow);
	mWindow.display();
}

void Game::gameOver()
{
	cout << "debut gameOver" << endl;
	Font font;
	if (!font.loadFromFile("bboron.ttf"))
	{
		cerr << "Erreur durant le chargement de la fonte" << endl;
	}
	Text game_over("GAME OVER\n YOU LOSE\n  (haha)", font, 100);
	FloatRect textRect = game_over.getGlobalBounds();
#pragma region info_getLocalBounds
	/* getLocalBounds:
	.left pour obtenir la coordonnée gauche du rectangle où est inscrit le texte
	.top pour la coordonnée haut du rectangle
	.width et .height pour respectivement la largeur et la hauteur du rectangle */
#pragma endregion info_getLocalBounds
	game_over.setPosition((WIDTH / 2.0f) - (textRect.width/2.0f), (HEIGHT / 2.0f) - (textRect.height/2.0f));
	Texte end(game_over, font, "GAME OVER\n YOU LOSE\n  (haha)", 100, white);
	mWindow.clear();
	end.draw(mWindow);
	mWindow.display();
	Sleep(3000);
	menuChoice();
	cout << "fin gameOver" << endl;
}
