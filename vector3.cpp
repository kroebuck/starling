#include "vector3.h"

Vector3::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(double nx, double ny, double nz) : x(x), y(y), z(z) {}

void Vector3::scale(double c) {
    x *= c;
    y *= c;
    z *= c;
}

void Vector3::add(Vector3 w) {
    x += w.x;
    y += w.y;
    z += w.z;
}

void Vector3::add(Vector3 w, double c) {
    x += c * w.x;
    y += c * w.y;
    z += c * w.z;
}

double Vector3::magnitude() {
    return sqrt(x*x + y*y + z*z);
}

void Vector3::set(double nx, double ny, double nz) {
    x = nx;
    y = ny;
    z = nz;
}