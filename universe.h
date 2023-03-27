#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <cmath>
#include <string>
#include <vector>


struct Vector2
{
	double x, y;
	Vector2() {
		x = 0.0;
		y = 0.0;
	}
	Vector2(double x, double y) : x(x), y(y) {}
	double magnitude() { return std::sqrt(x*x + y*y + 0.01); }
};

struct Vector3
{
	double x, y, z;
	Vector3() {
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
	Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
	double magnitude() { return sqrt(x*x + y*y + z*z + 0.01); } // softening parameter included
};

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
	int _dim;
    double _max = 0.0;
	std::vector<Particle*> _particles;
	Universe(int dim);
	//~Universe();
	void add(double m, double x, double y, double z, double vx, double vy, double vz);
	void addFromFile(std::string filename);
	void printParticle(Particle* b);
	void printUniverse();
	void update();
};

#endif