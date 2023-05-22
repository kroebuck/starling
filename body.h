#ifndef BODY_H
#define BODY_H

// #include "octant.h"
#include "physics.h"
#include "vector3.h"

class Body {
public:
    Vector3 _position, _velocity, _force;
    double _mass;

    Body(Vector3 position, Vector3 velocity, double mass);
    void update(double dt);
    Vector3 separationVectorTo(Body* b);
    void resetForce();
    void addForce(Body* b);
    // bool in(Octant* o);

    static Body* combine(Body* b1, Body* b2);
};

#endif