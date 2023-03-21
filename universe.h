#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <cmath>
#include <string>
#include <vector>


struct Vector2
{
	double x;
	double y;
	Vector2() {
		x = 0.0;
		y = 0.0;
	}
	Vector2(double x, double y)
		: x(x)
		, y(y)
	{}
	double magnitude() { return std::sqrt(x*x + y*y + 0.01); }
};

struct Vector3
{
	double x;
	double y;
	double z;
	Vector3(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	double magnitude() { return sqrt(x*x + y*y + z*z); }
};

struct Particle
{
	int id;
	double m;
	Vector2 pos, vel, da;
	Particle() {
		id = 0;
		m = 0.0;
		pos = Vector2(0.0, 0.0);
		vel = Vector2(0.0, 0.0);
		da = Vector2(0.0, 0.0);
	}
};

class Universe
{
public:
	int _dim;
	std::vector<Particle*> _particles;
	Universe(int dim);
	//~Universe();
	void add(double m, double x, double y, double vx, double vy);
	void addFromFile(std::string filename);
	void printParticle(Particle* b);
	void printUniverse();
	void update();
};

#endif