#include <iostream>
#include <string>
#include <chrono> // sleep
#include <thread> // sleep

#include "system.h"


int main()
{
	System system;
	system.addFromFile("initial_data.csv");

	while (true)
	{
		system.update();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}