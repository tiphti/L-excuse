#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <sstream>
#include <windows.h> // Sleep
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iterator>
#include <vector>
#include "game.h"
#include "timer.h"
#include "entity.h"

using namespace sf;
using namespace std;

#pragma region variables
const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
const float PlayerSpeed = 100.f;
const int FONT_SIZE = 80;
const int WIDTH = 800;
const int HEIGHT = 600;
//const float START_TIME = 7.0f;
std::string const red = "red";
std::string const white = "white";
std::string const pink = "pink";
std::string const black = "black";
#pragma endregion variables

/* Ce template permet de convertir un nombre (float, int, double) en string */
template <class T> string convertitNbEnString(T nb)
{
	ostringstream s;
	s << nb;
	return s.str();
}

Game::Game() :
	mWindow(VideoMode(WIDTH, HEIGHT, 32), "super jeu trop cool")
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

	/* configuration de l'horloge affichee dans le jeu */
	Timer secondes;
	Text text;
	Font font;
	int minutes = 6; // il est 6h dans le jeu lorsque le personnage se reveille
	text.setStyle(Text::Bold);
	if (!font.loadFromFile("digital-7.ttf"))
	{
		cerr << "Erreur durant le chargement de la fonte" << endl;
	}

	//introGame();
	secondes.Start(); // mise en marche de l'horloge

					  /* initialisation du jeu */
	Inventaire inventaire;
	Inventaire all_items;
	//Inventaire all_items(move(pTapisPlat));
	Sprite tapis_plat;
	Sprite tapis_retrousse;
	auto pTapisPlat = make_unique<Item>("tapis_plat", tapis_plat);
	auto pTapisRetrousse = make_unique<Item>("tapis_retrousse", tapis_retrousse);
	all_items.add(move(pTapisRetrousse));

	while (mWindow.isOpen())
	{
		/* affichage de l'horloge + mise en place des minutes */
		string minutesString = convertitNbEnString((int)minutes);
		string secondesString = convertitNbEnString((int)secondes.GetTime());
		Texte horlogeTxt(text, font, minutesString + "h: " + secondesString + "min", 30, white);
		if (convertitNbEnString((int)secondes.GetTime()) == "60")
		{
			++minutes;
			secondes.Reinitialize();
			secondes.Start();
		}

		render(horlogeTxt, all_items);
		processEvents(all_items);

		/*
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
		timeSinceLastUpdate -= TimePerFrame;
		processEvents();
		update(TimePerFrame);
		}*/
		/* (convertitNbEnString((int)secondes.GetTime()) == "50")
		{
		secondes.Pause();
		gameOver();
		}*/
	}
}

void Game::introGame()
{
	cout << "debut intro game" << endl;
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
	Sleep(1000); // pause de 1s
	cout << "fin intro game" << endl;
}

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

void Game::processEvents(Inventaire all_items)
{
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
			if (event.mouseButton.button == Mouse::Left)
			{
				cout << "click gauche ok" << endl;
				all_items.handleClickLeft(mWindow);
				break;
			}
		}
		default:
			break;
		}
	}
}
/*
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
}*/

void Game::render(Texte horlogeTxt, Inventaire all_items)
{
	mWindow.clear();
	horlogeTxt.draw(mWindow);
	all_items.drawInventaire(mWindow);
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
	game_over.setPosition((WIDTH / 2.0f) - (textRect.width / 2.0f), (HEIGHT / 2.0f) - (textRect.height / 2.0f)); // texte centre
	Texte end(game_over, font, "GAME OVER\n YOU LOSE\n  (haha)", 100, white);
	mWindow.clear();
	end.draw(mWindow);
	mWindow.display();
	Sleep(3000);
	menuChoice();
	cout << "fin gameOver" << endl;
}
