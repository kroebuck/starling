#ifndef OCTANT_H
#define OCTANT_H

#include "body.h"
#include "vector3.h"

class Octant {
public:
    Vector3 _position; // position of corner of quadrant closest to the origin
    double _length;
    
    Octant(Vector3 position, double length);
    bool contains(Vector3 point);
    double length();

    // Instantiate and return octant rooted at this octant
    Octant* FNW();
    Octant* FNE();
    Octant* FSW();
    Octant* FSE();
    Octant* BNW();
    Octant* BNE();
    Octant* BSW();
    Octant* BSE();
};

#endif