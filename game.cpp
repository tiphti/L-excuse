#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <windows.h> //Sleep
#include "game.h"
#include "timer.h"
#include "entity.h"
using namespace sf;
using namespace std;

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
const float PlayerSpeed = 100.f;
const int FONT_SIZE = 80;
const int WIDTH = 800; //largeur de la fenetre
const int HEIGHT = 600; //hauteur de la fenetre
std::string const red = "red";
std::string const white = "white";
std::string const pink = "pink";

template <class T> string convertitNbEnString(T nb) {
	ostringstream s;
	s << nb;
	return s.str();
}

Game::Game() :
	mWindow(sf::VideoMode(800, 600), "SFML Application")
	//,mPlayer()
{
	//mPlayer.setPosition(100.f, 100.f);
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Z)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::Q)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	startingGame();
	while (mWindow.isOpen())
	{
		startHorloge();
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
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
	Personnage chat("chat");
	mWindow.clear();
	//mPlayer.drawPerso(mWindow);
	//maman.drawPerso(mWindow);
	chat.draw(mWindow);
	mWindow.display();
}

void Game::startingGame()
{
	Font font;
	Text zzz("zzzz", font);
	Texte mText(zzz, "zzz", 50, white);
	if (!font.loadFromFile("digital-7.ttf"))
	{
		cout << "Erreur durant le chargement de la fonte" << endl;
	}
	//text.setFont(font);
	//text.setText(convertitNbEnString((int)horloge.getTime()));
	mText.setPosition(WIDTH / 2, HEIGHT / 2);
	mWindow.clear();
	mText.draw(mWindow);
	mWindow.display();
	Sleep(3000); // pause de 3s
}

void Game::startHorloge()
{
	Timer horloge;
	Font font;
	Text mText;
	if (!font.loadFromFile("digital-7.ttf"))
	{
		cout << "Erreur durant le chargement de la fonte" << endl;
	}
	string tempsReel = convertitNbEnString((int)horloge.getTime());
	Texte horlogeString(mText, tempsReel, 30, red);
	mText.setStyle(Text::Bold);
	mWindow.clear();
	horlogeString.draw(mWindow);
	mWindow.display();
}
