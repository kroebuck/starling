#include <iostream>
#include <string>
#include <chrono> // sleep
#include <thread> // sleep

#include "universe.h"


int main()
{
	Universe u(2);
	u.addFromFile("initial_data.csv");

    int count = 0;
	while (true)
	{
		u.update();
        count++;
        if (count == 100) {
            count = 0;
        }
		//std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}

	return 0;
}