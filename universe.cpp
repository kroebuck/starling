#include "universe.h"

Universe::Universe(int dim) {
	collisionMode = physics::CollisionMode::Inelastic;
	_dim = dim;
}

Universe::~Universe() {
	for (int i = 0; i < _particles.size(); i++) {
		delete _particles[i];
	}
}

void Universe::add(double m, double x, double y, double z, double vx, double vy, double vz)
{
	Particle* p = new Particle();

	p->id = _particles.size();
	p->mass = m;
	p->position.set(x, y, z);
	p->velocity.set(vx, vy, vz);
	p->acceleration.set(0,0,0);

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
	std::cout << p->id << " " << p->mass << " "
			  << p->position.x << " " << p->position.y << " " << p->position.z << " " 
  			  << p->velocity.x << " " << p->velocity.y << " " << p->velocity.z <<std::endl; 
}

void Universe::printUniverse()
{
	for (int i = 0; i < _particles.size(); i++)
	{
		printParticle(_particles[i]);
	}
}

void Universe::update()
{
	physics::evolve(_particles, collisionMode);

	printUniverse();
}