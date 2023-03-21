#include "universe.h"

#include <iostream>
#include <fstream> // read files
#include <string>
#include <vector>

Universe::Universe(int dim) {
	_dim = dim;
}

// Universe::~Universe() {
// 	// By assigning _bodies to an empty vector, the previous contents' memory is freed
// 	_bodies = new std::vector<Body*>();
// }

void Universe::add(double m, double x, double y, double vx, double vy)
{
	Particle* p = new Particle;

	p->id = _particles.size();
	p->m = m;
	p->pos.x = x;
	p->pos.y = y;
	p->vel.x = vx;
	p->vel.y = vy;

	_particles.push_back(p);
}

void Universe::addFromFile(std::string filename)
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

void Universe::printParticle(Particle* p)
{
	std::cout << p->id << " " << p->m << " "
			  << p->pos.x << " " << p->pos.y << " " 
  			  << p->vel.x << " " << p->vel.y << std::endl; 
}

void Universe::printUniverse()
{
	for (int i = 0; i < _particles.size(); i++)
	{
		printParticle(_particles[i]);
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

Vector2 getSeparationVector(Particle* p1, Particle* p2)
{
	Vector2 r;
	r.x = p2->pos.x - p1->pos.x;
	r.y = p2->pos.y - p1->pos.y;

	return r;
}

// F_r(r) = r / |r|^3
Vector2 F_r(Particle* p1, Particle* p2)
{
	Vector2 r = getSeparationVector(p1, p2);

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
void Universe::update()
{
	double dt = 0.01;
	double G = 100000.0;

	// update velocity/position & reset da to zero
	for (int i = 0; i < _particles.size(); i++) {
		_particles[i]->vel.x += dt / 2.0 * _particles[i]->da.x;
		_particles[i]->vel.y += dt / 2.0 * _particles[i]->da.y;

		_particles[i]->pos.x += dt * _particles[i]->vel.x;
		_particles[i]->pos.y += dt * _particles[i]->vel.y;

		_particles[i]->da.x = 0.0;
		_particles[i]->da.y = 0.0;
	}

	// calculate gravitational acceleration b/w all pairs of bodies
	for (int i = 0; i < _particles.size() - 1; i++) {
		for (int j = i + 1; j < _particles.size(); j++) {
			Vector2 r = F_r(_particles[i], _particles[j]); // r = r / |r|^3

			_particles[i]->da.x += _particles[j]->m * r.x;
			_particles[i]->da.y += _particles[j]->m * r.y;

			_particles[j]->da.x -= _particles[i]->m * r.x;
			_particles[j]->da.y -= _particles[i]->m * r.y;
		}
	}

	// update velocity of each body
	for (int i = 0; i < _particles.size(); i++) {
		_particles[i]->vel.x += G * dt / 2.0 * _particles[i]->da.x;
		_particles[i]->vel.y += G * dt / 2.0 * _particles[i]->da.y;
	}

	printUniverse();
}