#include <SFML/Graphics.hpp>
#pragma once

class Entity
{
public:
	Entity();
	virtual void setPosition(float posX, float posY) = 0;
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;
	virtual void draw(sf::RenderWindow &window) = 0;
private:
	std::vector<Entity*> tabEntity;
	sf::Vector2f mVelocity;
};

class Personnage : public Entity
{
public:
	Personnage(std::string name);
	void draw(sf::RenderWindow &window);
	void setPosition(float posX, float posY);
private:
	std::string mPersoName;
	sf::Sprite mSprite;
};

class Texte : public Entity
{
public:
	Texte();
	Texte(sf::Text text, std::string words, int size, std::string color);
	//void setUp(int size, std::string color);
	void draw(sf::RenderWindow &window);
	void setPosition(float posX, float posY);
private:
	sf::Text mText;
	std::string mWords;
	int mSize;
	std::string mColor;
};

class ObjetManipulable : public Entity
{
public:
	ObjetManipulable(std::string name);
	void draw(sf::RenderWindow &window);
	void setPosition(float posX, float posY);
private:
	std::string mObjName;
	sf::Sprite mSprite;
};
