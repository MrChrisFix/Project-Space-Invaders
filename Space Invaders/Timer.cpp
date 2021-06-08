#include "Timer.h"

Timer::Timer(int MAX_TIMER)
{
	this->MAX_TIME = MAX_TIMER;

	this->CURRENT_TIME = 0;

}

void Timer::update()
{
	if (this->MAX_TIME * 1.1 > this->CURRENT_TIME)
		CURRENT_TIME++;
}

bool Timer::avaliable()
{
	if (this->CURRENT_TIME > this->MAX_TIME)
	{
		this->CURRENT_TIME = 0;
		return true;
	}
	return false;
}

void Timer::reset()
{
	this->CURRENT_TIME = 0;
}
