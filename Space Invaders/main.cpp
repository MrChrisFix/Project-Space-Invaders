#include "Silnik.h"
#include <ctime>


int main()
{
	Silnik silnik;

	srand(time(NULL));

	while (silnik.isRunning())
	{
		silnik.update();

		silnik.render();
	}

	return 0;
}