#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.h"
using namespace sf;
using namespace std;

std::string const red = "red";
std::string const white = "black";
std::string const pink = "pink";

Entity::Entity()
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

Personnage::Personnage(string name):
	Entity(), mPersoName (name)
{
}

void Personnage::draw(sf::RenderWindow &window)
{
	Texture texture;
	if (mPersoName == "maman") {
		if (!texture.loadFromFile("maman.png"))
		{
			cerr << "erreur de chargement de l'image 'maman.png'" << endl;
		}
		//cout << "chargement de l'image 'maman.png' reussi" << endl;
	}
	if (mPersoName == "chat") {
		if (!texture.loadFromFile("chat.png"))
		{
			cerr << "erreur de chargement de l'image 'chat.png'" << endl;
		}
		//cout << "chargement de l'image 'chat.png' reussi" << endl;
	}
	if (mPersoName == "mPlayer") {
		if (!texture.loadFromFile("boy.png"))
		{
			cerr << "erreur de chargement de l'image 'boy.png'" << endl;
		}
		//cout << "chargement de l'image 'boy.png' reussi" << endl;
	}
	Sprite sprite(texture);
	//sprite.setPosition(100.f, 100.f);
	window.draw(sprite);
}

void Personnage::setPosition(float posX, float posY)
{
	mSprite.setPosition(posX, posY);
}

Texte::Texte():
	Entity()
{
}

Texte::Texte(Text text, string words, int size, string color):
	Entity(), mText (text), mWords (words), mSize (size), mColor (color)
{
	int R, V, B;
	if (mColor == white) { R = 255; V = 255; B = 255; }
	if (mColor == pink) { R = 253; V = 108; B = 158; }
	if (mColor == red) { R = 255; V = 0; B = 0; }
	mText.setColor(sf::Color(R, V, B));
	mText.setCharacterSize(mSize);
	mText.setString(mWords);
}

void Texte::draw(sf::RenderWindow &window)
{
	window.draw(mText);
}

void Texte::setPosition(float posX, float posY)
{
	mText.setPosition(posX, posY);
}

ObjetManipulable::ObjetManipulable(string name):
	Entity(), mObjName (name)
{
}

void ObjetManipulable::draw(sf::RenderWindow &window)
{
}

void ObjetManipulable::setPosition(float posX, float posY)
{
	mSprite.setPosition(posX, posY);
}
