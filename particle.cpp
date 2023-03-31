#include "particle.h"

Particle::Particle() = default;

Particle::Particle(int id, double mass, Vector3 position, Vector3 velocity, Vector3 acceleration) :
    id(id), mass(mass), position(position), velocity(velocity), acceleration(acceleration) {}