#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3 {
public:
    double x, y, z;

    Vector3();
    Vector3(double x, double y, double z);

    void scale(double c);
    void add(Vector3 w);
    void add(Vector3 w, double c);
    double magnitude();
    void set(double x, double y, double z);
};

#endif