#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "particle.h"
#include "physics.h"
#include "vector3.h"

#include <cmath>
#include <fstream> // read files
#include <iostream>
#include <string>
#include <vector>

class Universe
{
public:
	physics::CollisionMode collisionMode;
	int _dim;
    double _max = 0.0;
	std::vector<Particle*> _particles;

	Universe(int dim);
	~Universe();

	void add(double m, double x, double y, double z, double vx, double vy, double vz);
	void addFromFile(std::string filename);
	void printParticle(Particle* b);
	void printUniverse();
	void update();
};

#endif