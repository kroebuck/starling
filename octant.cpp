#include "octant.h"

Octant::Octant(Vector3 position, double length) {
    _position = position;
    _length = length;
}

/*
* Does the inputted body lie within this octant?
*/
bool Octant::contains(Vector3 point) {
    return (point.x >= _position.x && point.x <= _position.x + _length) &&
           (point.y >= _position.y && point.y <= _position.y + _length) && 
           (point.z >= _position.z && point.z <= _position.z + _length);
}

/*
* Returns the side length of this octant.
*/
double Octant::length() {
    return _length;
}

/*
* Return an instance of the child octant that the inputted point lies in.
*/
Octant* Octant::generateChildOctant(Vector3 point) {
    if (!contains(point)) return NULL;

    // parameters for child octant
    double newLength = _length / 2.0;
    double nx = _position.x;
    double ny = _position.y;
    double nz = _position.z;

    // update parameters to place point in correct octant
    if (point.x <= _position.x + _length) nx += newLength;
    if (point.y <= _position.y + _length) ny += newLength;
    if (point.z <= _position.z + _length) nz += newLength;

    return new Octant(Vector3(nx, ny, nz), newLength);
}