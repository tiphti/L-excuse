#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>    // std::swap
#include <vector>
#include "entity.h"

using namespace sf;
using namespace std;

std::string const red = "red";
std::string const white = "white";
std::string const pink = "pink";
std::string const black = "black";

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
	}
	if (mPersoName == "chat") {
		if (!texture.loadFromFile("chat.png"))
		{
			cerr << "erreur de chargement de l'image 'chat.png'" << endl;
		}
	}
	Sprite sprite(texture);
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

Texte::Texte(Text text, Font font, string words, int size, string color):
	Entity(), mText (text), mFont (font), mWords (words), mSize (size), mColor (color)
{
	int R = 255, V = 255, B = 255;
	if (mColor == white) { R = 255; V = 255; B = 255; }
	if (mColor == pink) { R = 253; V = 108; B = 158; }
	if (mColor == red) { R = 255; V = 0; B = 0; }
	if (mColor == black) { R = 0; V = 0; B = 0; }
	mText.setColor(sf::Color(R, V, B));
	mText.setCharacterSize(mSize);
	mText.setString(mWords);
	mText.setFont(mFont);
}

void Texte::draw(sf::RenderWindow &window)
{
	window.draw(mText);
}

void Texte::setPosition(float posX, float posY)
{
	mText.setPosition(posX, posY);
}

Item::Item(string name, Sprite sprite):
	Entity(), mItemName (name), mSprite (sprite)
{
}

void Item::draw(sf::RenderWindow &window)
{
	Texture texture;
	if (mItemName == "tapis_plat") {
		if (!texture.loadFromFile("tapis_plat.png"))
		{
			cerr << "erreur de chargement de l'image 'tapis_plat'.png'" << endl;
		}
	}
	else if (mItemName == "tapis_retrousse") {
		if (!texture.loadFromFile("tapis_retrousse.png"))
		{
			cerr << "erreur de chargement de l'image 'tapis_retrousse'.png'" << endl;
		}
	}
	mSprite = Sprite(texture);
	if (mItemName == "tapis_plat") {
		mSprite.setScale(0.1f, 0.1f);
		mSprite.setPosition(50, 200);
	}
	else if (mItemName == "tapis_retrousse") {
		mSprite.setScale(0.1f, 0.1f);
		mSprite.setPosition(400, 300);
	}
	window.draw(mSprite);
}

void Item::setPosition(float posX, float posY)
{
	mSprite.setPosition(posX, posY);
}

void Item::setScale(float scaleX, float scaleY)
{
	mSprite.setScale(scaleX, scaleY);
}

FloatRect Item::get_global_bounds()
{
	//return mSprite.getGlobalBounds();
	return mSprite.getGlobalBounds();
}

Inventaire::Inventaire(vector<Item> tab):
	tabInventaire (tab)
{
}

void Inventaire::add(Item item)
{
		tabInventaire.push_back(item);
}

void Inventaire::remove()
{
	tabInventaire.pop_back();
}

void Inventaire::swap(Item item)
{
	std::swap(item, tabInventaire.back());
}

void Inventaire::drawInventaire(RenderWindow &window)
{
	//for (int i = 0; i != tabInventaire.size(); ++i)
	for (auto i : tabInventaire)
	{
		i.draw(window);
	}
}

void Inventaire::processEvents(RenderWindow &window)
{/*
	Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			window.close();
			break;
		case Event::MouseButtonReleased:
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				//if (ismouseonAsprite(window) == true)
				{
					cout << "click gauche ok" << endl;
					//cout << "click gauche ok: mouse on A sprite ok" << endl;
					//all_items.handleClickOnSprite(all_items.ismouseonAsprite(mWindow));
					//handleClickLeft(window);
					for (Item item : tabInventaire)
					{
						if (isMouseOnThisSprite(window, item) == true)
						{
							swap(item, tabInventaire.back());
							remove();
							cout << "swap ok" << endl;
						}
						else { cout << "missed sprite" << endl; }
					}
				}
				//else { cout << "click gauche ok: missed, are you dumb ?" << endl; }
				//handlePlayerInput(false);
				break;
			}
		}
		default:
			break;
		}
	}*/
}

bool Inventaire::isMouseOnThisSprite(RenderWindow &window, Item item)
{
	FloatRect rect = item.get_global_bounds();
	if ((rect.left <= (Mouse::getPosition().x - window.getPosition().x))
		&& ((Mouse::getPosition().x - window.getPosition().x) <= (rect.left + rect.width))
		&& (rect.top <= (Mouse::getPosition().y - window.getPosition().y))
		&& ((Mouse::getPosition().y - window.getPosition().y) <= (rect.top + rect.height)))
	{
		return true;
	}
	else { return false; }
}

bool Inventaire::ismouseonAsprite(RenderWindow &window)
{
	for (Item it : tabInventaire)
	{
		//if (isMouseOnSprite(window, it) == true) {
		FloatRect rect = it.get_global_bounds();
		if ((rect.left <= (Mouse::getPosition().x - window.getPosition().x))
			&& ((Mouse::getPosition().x - window.getPosition().x) <= (rect.left + rect.width))
			&& (rect.top <= (Mouse::getPosition().y - window.getPosition().y))
			&& ((Mouse::getPosition().y - window.getPosition().y) <= (rect.top + rect.height)))
		{
			return true;
		}
		else { return false; }
	}
}

void Inventaire::handleClickLeft(RenderWindow &window, bool isOnSprite)
{
	if (!tabInventaire.empty())
	{
		for (auto it : tabInventaire)
		{
			//Item item = *it;
			FloatRect rect = it.get_global_bounds();
			if ((rect.left <= (Mouse::getPosition().x - window.getPosition().x))
				&& ((Mouse::getPosition().x - window.getPosition().x) <= (rect.left + rect.width))
				&& (rect.top <= (Mouse::getPosition().y - window.getPosition().y))
				&& ((Mouse::getPosition().y - window.getPosition().y) <= (rect.top + rect.height)))
			{
				std::swap(it, tabInventaire.back());
				tabInventaire.pop_back();
				cout << "swap + remove ok" << endl;
			}
			else { cout << "missed" << endl; }
		}
	}
}

