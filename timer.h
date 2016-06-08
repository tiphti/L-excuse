#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Timer
{
public:
	Timer();
	float getTime();
private:
	sf::Clock mClock;
};
