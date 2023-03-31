#include "universe.h"

#include <cmath>
#include <iostream>
#include <fstream> // read files
#include <string>
#include <vector>

const double MINIMUM_MAGNITUDE = 4.0;

Universe::Universe(int dim) {
	collisionMode = physics::CollisionMode::Collisionless;
	_dim = dim;
}

Universe::~Universe() {
	for (int i = 0; i < _particles.size(); i++) {
		delete _particles[i];
	}
}

void Universe::add(double m, double x, double y, double z, double vx, double vy, double vz)
{
	Particle* p = new Particle;

	p->id = _particles.size();
	p->m = m;
	p->pos.x = x;
	p->pos.y = y;
	p->pos.z = z;
	p->vel.x = vx;
	p->vel.y = vy;
	p->vel.z = vz;

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

		add(values[0], values[1], values[2], values[3], values[4], values[5], values[6]);
	}

}

void Universe::printParticle(Particle* p)
{
	std::cout << p->id << " " << p->m << " "
			  << p->pos.x << " " << p->pos.y << " " << p->pos.z << " " 
  			  << p->vel.x << " " << p->vel.y << " " << p->vel.z <<std::endl; 
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

// Vector3 add(Vector3 v, Vector3 w)
// {
// 	v.x += w.x;
// 	v.y += w.y;
// 	v.z += w.z;
// 	return v;
// }

// void scale(Vector3& v, double c)
// {
// 	v.x *= c;
// 	v.y *= c;
// 	v.z *= c;
// }

Vector3 getSeparationVector(Particle* p1, Particle* p2)
{
	Vector3 r;
	r.x = p2->pos.x - p1->pos.x;
	r.y = p2->pos.y - p1->pos.y;
	r.z = p2->pos.z - p1->pos.z;

	return r;
}

// F_r(r) = r / |r|^3
Vector3 F_r(Particle* p1, Particle* p2)
{
	Vector3 r = getSeparationVector(p1, p2);

	// x = 1 / |r|^3
	double mag =  1 / std::pow(std::max(r.magnitude(), MINIMUM_MAGNITUDE), 3);

	r.scale(mag);

	return r;
}

//
//
//

void Universe::update()
{
	if (collisionMode == physics::CollisionMode::Collisionless) {
		//
	}

	double dt = 0.01;
	double G = 100000.0;

	// update velocity/position & reset da to zero
	for (int i = 0; i < _particles.size(); i++) {
		_particles[i]->vel.add(_particles[i]->da, dt / 2.0); // v_i += (dt/2) * a_i
		_particles[i]->pos.add(_particles[i]->vel, dt);		 // x_i += dt * v_i
		_particles[i]->da.scale(0.0);						 // a_i = 0
	}

	// calculate gravitational acceleration b/w all pairs of bodies
	for (int i = 0; i < _particles.size() - 1; i++) {
		for (int j = i + 1; j < _particles.size(); j++) {
			Vector3 r = F_r(_particles[i], _particles[j]);   // r = r / |r|^3

			_particles[i]->da.add(r, _particles[j]->m);		 // da_i += m * r
			_particles[j]->da.add(r, -1 * _particles[i]->m); // da_j -= m * r
		}
	}

	// update velocity of each body
	for (int i = 0; i < _particles.size(); i++) {
		_particles[i]->vel.add(_particles[i]->da, G * dt / 2.0); // v_i += (G * dt / 2) * a_i
	}

	printUniverse();
}