#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "body.h"
#include "octant.h"
#include "barneshuttree.h"
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
	std::vector<Body*> _bodies;
	BarnesHutTree* _root;

	Universe();
	~Universe();

	void add(double m, double x, double y, double z, double vx, double vy, double vz);
	void addFromFile(std::string filename);
	void printBody(Body* b);
	void printUniverse();
	void resetTree();
	void fillTree();
	void update();
};

#endif