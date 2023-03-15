#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

struct Body
{
	int id;
	double m, x, y, vx, vy;
};

class System
{
public:
	std::vector<Body*> _bodies;
	System();
	void add(double m, double x, double y, double vx, double vy);
	void addFromFile(std::string filename);
	void printBody(Body* b);
	void printSystem();
	void update();
};

#endif