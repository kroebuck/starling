#ifndef BODY_H
#define BODY_H

#include "vector3.h"

class Body {
    Vector3 _position, _velocity, _force;
    double _mass;

    Body(Vector3 position, Vector3 velocity, double mass);
    void update(double dt);
    double distanceTo(Body* b);
    void resetForce();
    void addForce(Body* b);
    bool in(Octant* o);
};

#endif