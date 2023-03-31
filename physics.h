#ifndef PHYSICS_H
#define PHYSICS_H

#include "particle.h"
#include "vector3.h"

#include <cmath>
#include <vector>

namespace physics {
    enum class CollisionMode {
        Elastic,
        Inelastic,
        Collisionless
    };

    extern double dt;
    extern double G;

    void update(std::vector<Particle*>& p, CollisionMode mode);
}

#endif