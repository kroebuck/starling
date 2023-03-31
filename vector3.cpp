#include "vector3.h"

#include <cmath>

Vector3::Vector3() = default;
Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

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