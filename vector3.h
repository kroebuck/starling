#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3 {
public:
    double x, y, z;

    Vector3();
    Vector3(double x, double y, double z);
    Vector3(const Vector3&);

    void scale(double c);
    void add(Vector3 w);
    void add(Vector3 w, double c);
    double magnitude();
    void set(double x, double y, double z);

    static Vector3 difference(Vector3 v, Vector3 w);
    static Vector3 sum(Vector3 v, Vector3 w);
};

#endif