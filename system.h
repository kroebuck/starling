#ifndef SYSTEM_H
#define SYSTEM_H

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

struct Body
{
	int id;
	double m;
	Vector2 pos, vel, da;
	Body() {
		id = 0;
		m = 0.0;
		pos = Vector2(0.0, 0.0);
		vel = Vector2(0.0, 0.0);
		da = Vector2(0.0, 0.0);
	}
};

class System
{
public:
	int _dim;
	std::vector<Body*> _bodies;
	System(int dim);
	//~System();
	void add(double m, double x, double y, double vx, double vy);
	void addFromFile(std::string filename);
	void printBody(Body* b);
	void printSystem();
	void update();
};

#endif