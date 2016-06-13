#include <SFML/Graphics.hpp>
#include <vector>
#pragma once

class Entity
{
public:
	Entity();
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void setPosition(float posX, float posY) = 0;
private:
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
	Texte(sf::Text text, sf::Font font, std::string words, int size, std::string color);
	//void setUp(int size, std::string color);
	void draw(sf::RenderWindow &window);
	void setPosition(float posX, float posY);
private:
	sf::Text mText;
	sf::Font mFont;
	std::string mWords;
	int mSize;
	std::string mColor;
};

class Item : public Entity
{
public:
	Item(std::string name, sf::Sprite sprite);
	void draw(sf::RenderWindow &window);
	void setPosition(float posX, float posY);
	void setScale(float scaleX, float scaleY);
	sf::FloatRect get_global_bounds();
	//bool isMouseOnSprite();
private:
	std::string mItemName;
	sf::Sprite mSprite;
};

class Inventaire
{
public:
	Inventaire(std::vector<Item> tab);
	void add(Item item);
	void remove();
	void swap(Item item);
	void drawInventaire(sf::RenderWindow &window);
	bool isMouseOnThisSprite(sf::RenderWindow &window, Item item);
	void processEvents(sf::RenderWindow &window);
	bool ismouseonAsprite(sf::RenderWindow &window);
	void handleClickLeft(sf::RenderWindow &window, bool isOnSprite);
private:
	std::vector<Item> tabInventaire;
};
