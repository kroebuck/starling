#include "system.h"

#include <iostream>
#include <fstream> // read files
#include <string>

System::System() = default;

void System::add(double m, double x, double y, double vx, double vy)
{
	Body* b = new Body;
	b->id = _bodies.size();
	b->m = m;
	b->x = x;
	b->y = y;
	b->vx = vx;
	b->vy = vy;

	_bodies.push_back(b);
}

void System::addFromFile(std::string filename)
{
	std::ifstream infile("initial_data.csv");
	std::string line;
	std::getline(infile, line); // skip first row (labels for what each column is)
	while (std::getline(infile, line))
	{
		// Tokenize line to get inital mass, position, and velocity of current body
		int prev = 0, pos;
		double val = 0.0;
		std::vector<double> values;
		while ((pos = line.find_first_of(",", prev)) != std::string::npos)
		{
			val = std::stod(line.substr(0, pos));
			values.push_back(val);
			line.erase(0, pos + 1);
		}
		if (prev < line.length()) // Get last token on line
		{
			val = std::stod(line.substr(0, pos));
			values.push_back(val);
		}

		add(
			values[0],
			values[1],
			values[2],
			values[3],
			values[4]
		);
	}

}

void System::printBody(Body* b)
{
	std::cout << b->id << " " << b->m << " " << 
				 b->x  << " " << b->y << " " << 
				 b->vx << " " << b->vy << std::endl;
}

void System::printSystem()
{
	for (int i = 0; i < _bodies.size(); i++)
	{
		printBody(_bodies[i]);
	}
}

// TODO: Implement/call actual n-body physics here
void System::update()
{
	for (int i = 0; i < _bodies.size(); i++) {
		_bodies[i]->x += 1.0 * (i+1);
		_bodies[i]->y += 1.0 * (i+1);
	}

	printSystem();
}