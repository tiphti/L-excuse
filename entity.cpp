#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.h"

using namespace std;

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
	Entity(), mName (name)
{
}

void Personnage::drawPerso(sf::RenderWindow &window)
{
	std::vector<Entity*> tabPerso;
	sf::Texture texture;
	if (mName == "maman") {
		if (!texture.loadFromFile("maman.png"))
		{
			cout << "erreur de chargement de l'image 'maman.png'" << endl;
		}
		cout << "chargement de l'image 'maman.png' reussi" << endl;
	}
	if (mName == "chat") {
		if (!texture.loadFromFile("chat.png"))
		{
			cout << "erreur de chargement de l'image 'chat.png'" << endl;
		}
		cout << "chargement de l'image 'chat.png' reussi" << endl;
	}
	if (mName == "mPlayer") {
		if (!texture.loadFromFile("boy.png"))
		{
			cout << "erreur de chargement de l'image 'boy.png'" << endl;
		}
		cout << "chargement de l'image 'boy.png' reussi" << endl;
	}
	sf::Sprite sprite(texture);
	//sprite.setPosition(100.f, 100.f);
	window.draw(sprite);
}
