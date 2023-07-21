#include "universe.h"

Universe::Universe() {
	collisionMode = physics::CollisionMode::Collisionless;
	_dim = 3;
}

Universe::~Universe() {
	for (int i = 0; i < _bodies.size(); i++) {
		delete _bodies[i];
	}
}

void Universe::add(double m, double x, double y, double z, double vx, double vy, double vz)
{
	Body* b = new Body(Vector3(x,y,z), Vector3(vx,vy,vz), m);
	_bodies.push_back(b);
}

void Universe::addFromFile(std::string filename)
{
	std::ifstream infile("initial_data.csv");
	std::string line;
	std::getline(infile, line); // Skip first row (column labels)
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

// TODO: Add id property to Body class
void Universe::printBody(Body* b)
{
	// std::cout << b->id << " " << b->_mass << " "
	// 		  << b->_position.x << " " << b->_position.y << " " << b->_position.z << " " 
  	// 		  << b->_velocity.x << " " << b->_velocity.y << " " << b->_velocity.z <<std::endl; 
	std::cout << "0" << " " << b->_mass << " "
			  << b->_position.x << " " << b->_position.y << " " << b->_position.z << " " 
  			  << b->_velocity.x << " " << b->_velocity.y << " " << b->_velocity.z <<std::endl; 
}

void Universe::printUniverse()
{
	for (int i = 0; i < _bodies.size(); i++)
	{
		printBody(_bodies[i]);
	}
}

void Universe::resetTree() {
	double len = 10000;
	Octant* o = new Octant(Vector3(-1 * len, -1 * len, -1 * len), 2 * len);
	_root = new BarnesHutTree(o);
}

void Universe::fillTree() {
	for (int i = 0; i < _bodies.size(); i++) {
		_root->insert(_bodies[i]);
	}
}

void Universe::update()
{
	resetTree();
	fillTree();
	
	physics::evolve(_bodies, collisionMode);

	printUniverse();
}