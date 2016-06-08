#include "timer.h"
using namespace sf;

Timer::Timer()
{
}

float Timer::getTime() // retourne la duree ecoulee en secondes
{
	Time time = mClock.getElapsedTime();
	float sec = time.asSeconds();
	return sec;
}
