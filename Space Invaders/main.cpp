#include "Silnik.h";


int main()
{
	Silnik silnik;

	while (silnik.isRunning())
	{
		silnik.update();

		silnik.render();
	}

	return 0;
}