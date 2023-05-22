#include "body.h"

Body::Body(Vector3 position, Vector3 velocity, double mass) : _position(position), _velocity(velocity), _mass(mass) {}

/*
* Step this body forward in time by updating position and velocity.
*/
void Body::update(double dt) {
    _velocity.add(_force, dt / _mass);
    _position.add(_velocity, dt);
}

/* 
* Returns separation vector pointing from current body to inputted body
*/
Vector3 Body::separationVectorTo(Body* b) {
    double dx = b->_position.x - _position.x;
    double dy = b->_position.y - _position.y;
    double dz = b->_position.z - _position.z;
    return Vector3(dx, dy, dz);
}

/*
* Set the _force vector to all zeros.
*/
void Body::resetForce() {
    _force.set(0,0,0);
}

/*
* Calculate gravitational force between this body and the inputted body.
* Add result to this body's _force vector.
*/
void Body::addForce(Body* b) {
    Vector3 separation = separationVectorTo(b);
    double distance = separation.magnitude();
    double forceMagnitude = (physics::G * _mass * b->_mass) / (distance * distance);
    _force.add(separation, forceMagnitude / distance);
}

/*
* Is this body contained within the inputted octant?
*/
// bool Body::in(Octant* o) {
//     return o->contains(_position);
// }

/*
* A static method for adding two bodies by combining their position and mass,
* and returning the resulting body to represent center of gravity for a quadrant.
*/
static Body* combine(Body* b1, Body* b2) {
    // p' = (m1p1 + m2p2) / (m1 + m2)
    Vector3 newPosition;
    Vector3 newVelocity;
    newPosition.add(b1->_position, b1->_mass);
    newPosition.add(b2->_position, b2->_mass);
    newPosition.scale(1 / (b1->_mass + b2->_mass));
    return new Body(newPosition, newVelocity, b1->_mass + b2->_mass);
}