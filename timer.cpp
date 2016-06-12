#include "Timer.h"

Timer::Timer() : myElapsedTime(0.0f), myState(Paused)
{}

void Timer::Start()
{
	if (myState != Started) // On ne lance pas le timer si il est déja lancé
	{
		myClock.restart();
		myState = Started;
	}
}

void Timer::Pause()
{
	if (myState != Paused) // On ne mets pas en pause le timer si il est déja en pause
	{
		myState = Paused;
		sf::Time t = myClock.getElapsedTime();
		float sec = t.asMilliseconds();
		myElapsedTime += sec;
	}
}

void Timer::Reinitialize()
{
	myClock.restart();
	Pause();
	myElapsedTime = 0.0f;
}

float Timer::GetTime()
{
	float time;
	if (myState == Paused)
	{
		time = myElapsedTime;
	}
	else
	{
		sf::Time t = myClock.getElapsedTime();
		float sec = t.asSeconds();
		time = sec + myElapsedTime;
	}
	return time;
}
