#include <iostream>
#include <string>
#include <chrono> // sleep
#include <thread> // sleep

#include "universe.h"


int main()
{
	Universe u(2);
	u.addFromFile("initial_data.csv");

	while (true)
	{
		u.update();
		//std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}

	return 0;
}