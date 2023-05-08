#include "body.h"

Body::Body(Vector3 position, Vector3 velocity, double mass) : _position(position), _velocity(velocity), mass(mass);

void Body::update(double dt) {
    _velocity.add(_force, dt / _mass);
    _position.add(_velocity, dt);
}

double Body::distanceTo(Body* b) {
    double dx = _position.x - b->_position.x;
    double dy = _position.y - b->_position.y;
    double dz = _position.z - b->_position.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

void Body::resetForce()

void Body::addForce(Body* b)

bool Body::in(Octant* o) {
    return o->contains(_position);
}