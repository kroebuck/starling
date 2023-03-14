#include <iostream>
#include <string>
#include <vector>

// read files
#include <fstream>
//#include <sstream>

// sleep
#include <chrono>
#include <thread>

struct Body
{
	int id;
	double m, x, y, vx, vy;
};

void update();
void printBody(Body*);
void printAndSleep();

int main()
{
	std::vector<Body*> bodies;

	// Read file
	std::ifstream infile("initial_data.csv");
	std::string line;
	std::getline(infile, line); // skip first row (labels for what each column is)
	int id = 0;
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

		// Construct body object
		Body* b = new Body;
		b->id = id;
		b->m = values[0];
		b->x = values[1];
		b->y = values[2];
		b->vx = values[3];
		b->vy = values[4];

		bodies.push_back(b);
		id++;
	}

	for (int i = 0; i < bodies.size(); i++) {
		printBody(bodies[i]);
	}

	// while (true)
	// {
	// 	update();
	// }


	return 0;
}

void printBody(Body* b) {
	std::cout << "id: " << b->id << std::endl;
	std::cout << "  m:  " << b->m << std::endl;
	std::cout << "  x:  " << b->x << std::endl;
	std::cout << "  y:  " << b->y << std::endl;
	std::cout << "  vx: " << b->vx << std::endl;
	std::cout << "  vy: " << b->vy << std::endl;
}

void update()
{

}

void printAndSleep()
{
	for (int i = 0; i < 100000; i++) {
		std::cout << i << '\n';//std::endl;
		if (i % 10 == 0) std::cout << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}