#include <iostream>
#include <string>
#include <chrono> // sleep
#include <thread> // sleep

#include "universe.h"


int main()
{
	Universe u;
	u.addFromFile("initial_data.csv");

	while (true)
	{
		u.update();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}

// m,x,y,z,vx,vy,vz
// 1,-10,-20,5,1,0.1,1
// 1,5,2.5,2.5,-0.1,-0.1,-0.5
// 1,-12,0,0,1,0,0
// 1,12,0,10,-1,0,0
// 1,0,8,0,0,-1,3
// 1,3,8,0,0,-1,3
// 1,-10,8,0,1,-1,3
// 1,0,2,-10,0,-1,2
// 1,6,0,4,0,-1,-1

// m,x,y,z,vx,vy,vz
// 1,-5,0,0,0,40,0
// 1,2,0,0,0,-40,0
// 1,-2,-2,0,-20,20,0
// 1,0,3,0,-30,0,0
// 1,3,3,0,30,0,0
// 1,-8,3,0,30,10,0
// 10,9,9,0,-40,40,0

// for testing inelastic collisions.
// m,x,y,z,vx,vy,vz
// 2,-5,0,0,40,0,0
// 1,5,0,0,-40,0,0