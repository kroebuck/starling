#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector3.h"

class Particle {
public:
    int id;
    double mass;
    Vector3 position, velocity, acceleration;

    Particle();
    Particle(int id, double mass, Vector3 position, Vector3 velocity, Vector3 acceleration);
};

#endif