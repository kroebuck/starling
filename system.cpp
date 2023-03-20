#include "system.h"

#include <iostream>
#include <fstream> // read files
#include <string>
#include <vector>

System::System(int dim) {
	_dim = dim;
}

// System::~System() {
// 	// By assigning _bodies to an empty vector, the previous contents' memory is freed
// 	_bodies = new std::vector<Body*>();
// }

void System::add(double m, double x, double y, double vx, double vy)
{
	Body* b = new Body;

	b->id = _bodies.size();
	b->m = m;
	b->pos.x = x;
	b->pos.y = y;
	b->vel.x = vx;
	b->vel.y = vy;

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

		add(values[0], values[1], values[2], values[3], values[4]);
	}

}

void System::printBody(Body* b)
{
	std::cout << b->id << " " << b->m << " "
			  << b->pos.x << " " << b->pos.y << " " 
  			  << b->vel.x << " " << b->vel.y << std::endl; 
}

void System::printSystem()
{
	for (int i = 0; i < _bodies.size(); i++)
	{
		printBody(_bodies[i]);
	}
}

//
// HELPER FUNCTIONS
//

Vector2 add(Vector2 v, Vector2 w)
{
	v.x += w.x;
	v.y += w.y;
	return v;
}

Vector2 scale(Vector2 v, double c)
{
	v.x *= c;
	v.y *= c;
	return v;
}

Vector2 getSeparationVector(Body* b1, Body* b2)
{
	Vector2 r;
	r.x = b2->pos.x - b1->pos.x;
	r.y = b2->pos.y - b1->pos.y;

	return r;
}

// F_r(r) = r / |r|^3
Vector2 F_r(Body* b1, Body* b2)
{
	Vector2 r = getSeparationVector(b1, b2);

	// x = 1 / |r|^3
	double mag = r.magnitude();
	mag = mag * mag * mag;
	mag = 1 / mag;

	return scale(r, mag);
}

//
//
//

// TODO: Implement/call actual n-body physics here
void System::update()
{
	double dt = 0.01;
	double G = 100.0;

	// for (int i = 0; i < _bodies.size(); i++) {
	// 	_bodies[i]->pos.x += _bodies[i]->vel.x * dt;
	// 	_bodies[i]->pos.y += _bodies[i]->vel.y * dt;
	// }

	// update velocity/position & reset da to zero
	for (int i = 0; i < _bodies.size(); i++) {
		_bodies[i]->vel.x += dt / 2.0 * _bodies[i]->da.x;
		_bodies[i]->vel.y += dt / 2.0 * _bodies[i]->da.y;

		_bodies[i]->pos.x += dt * _bodies[i]->vel.x;
		_bodies[i]->pos.y += dt * _bodies[i]->vel.y;

		_bodies[i]->da.x = 0.0;
		_bodies[i]->da.y = 0.0;
	}

	// calculate gravitational acceleration b/w all pairs of bodies
	for (int i = 0; i < _bodies.size() - 1; i++) {
		for (int j = i + 1; j < _bodies.size(); j++) {
			Vector2 r = F_r(_bodies[i], _bodies[j]); // r = r / |r|^3

			_bodies[i]->da.x += _bodies[j]->m * r.x;
			_bodies[i]->da.y += _bodies[j]->m * r.y;

			_bodies[j]->da.x -= _bodies[i]->m * r.x;
			_bodies[j]->da.y -= _bodies[i]->m * r.y;
		}
	}

	// update velocity of each body
	for (int i = 0; i < _bodies.size(); i++) {
		_bodies[i]->vel.x += G * dt / 2.0 * _bodies[i]->da.x;
		_bodies[i]->vel.y += G * dt / 2.0 * _bodies[i]->da.y;
	}

	printSystem();
}