#pragma once
class Timer
{
	int MAX_TIME;
	int CURRENT_TIME;

public:
	Timer(int MAX_TIMER);

	void update();

	bool avaliable();

	void reset();

};

