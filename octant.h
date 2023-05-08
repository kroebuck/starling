#ifndef OCTANT_H
#define OCTANT_H

#include "vector3.h"

class Octant {
public:
    int _numberOfParticles;
    double _mass;
    Vector3 _centerOfMass;
    Vector3 _position; // position of corner of quadrant closest to the origin
    double _length;
    
    Octant(Vector3 position, double length);
    bool contains(double x, double y);
    double length();

    // Instantiate and return octant rooted at this octant
    // z-direction: F = front, B = back
    // y-direction: N = north, S = south
    // x-direction: W = west, E = east
    Octant* FNW(), FNE(), FSW(), FSE(), BNW(), BNE(), BSW(), BSE();
};

#endif