#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "physics.h"
#include "vector3.h"

#include <cmath>
#include <string>
#include <vector>


// struct Vector3
// {
// 	double x, y, z;
// 	Vector3() {
// 		x = 0.0;
// 		y = 0.0;
// 		z = 0.0;
// 	}
// 	Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
// 	double magnitude() { return sqrt(x*x + y*y + z*z); }
// };

struct Particle
{
	int id;
	double m;
	Vector3 pos, vel, da;
	Particle() {
		id = 0;
		m = 0.0;
		pos = Vector3();
		vel = Vector3();
		da = Vector3();
	}
};

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