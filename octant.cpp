#include "octant.h"

Octant::Octant(Vector3 position, double length) : _position(position), _length(length) {}

bool Octant::contains(Vector3 point) {
    return (point.x >= _position.x && point.x <= _position.x + _length) &&
           (point.y >= _position.y && point.y <= _position.y + _length) && 
           (point.z >= _position.z && point.z <= _position.z + _length);
}

double Octant::length() {
    return _length;
}

Octant* Octant::FNW() {
    double newLength = _length / 2.0;
    double nx = _position.x;
    double ny = _position.y + newLength;
    double nz = _position.z + newLength;
    return Octant(Vector3(nx, ny, nz), newLength);
}

Octant* Octant::FNE() {
    double newLength = _length / 2.0;
    double nx = _position.x + newLength;
    double ny = _position.y + newLength;
    double nz = _position.z + newLength;
    return Octant(Vector3(nx, ny, nz), newLength);
}

Octant* Octant::FSW() {
    double newLength = _length / 2.0;
    double nx = _position.x;
    double ny = _position.y;
    double nz = _position.z + newLength;
    return Octant(Vector3(nx, ny, nz), newLength);
}

Octant* Octant::FSE() {
    double newLength = _length / 2.0;
    double nx = _position.x + newLength;
    double ny = _position.y;
    double nz = _position.z + newLength;
    return Octant(Vector3(nx, ny, nz), newLength);
}

Octant* Octant::BNW() {
    double newLength = _length / 2.0;
    double nx = _position.x;
    double ny = _position.y + newLength;
    double nz = _position.z;
    return Octant(Vector3(nx, ny, nz), newLength);
}

Octant* Octant::BNE() {
    double newLength = _length / 2.0;
    double nx = _position.x + newLength;
    double ny = _position.y + newLength;
    double nz = _position.z;
    return Octant(Vector3(nx, ny, nz), newLength);
}

Octant* Octant::BSW() {
    double newLength = _length / 2.0;
    double nx = _position.x;
    double ny = _position.y;
    double nz = _position.z;
    return Octant(Vector3(nx, ny, nz), newLength);
}

Octant* Octant::BSE() {
    double newLength = _length / 2.0;
    double nx = _position.x + newLength;
    double ny = _position.y;
    double nz = _position.z;
    return Octant(Vector3(nx, ny, nz), newLength);
}