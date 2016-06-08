#include <SFML/Graphics.hpp>
#pragma once

class Entity
{
public:
	Entity();
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;
private:
	sf::Vector2f mVelocity;
};

class Personnage : public Entity
{
public:
	Personnage(std::string name);
	void drawPerso(sf::RenderWindow &window);
private:
	std::string mName;
};
