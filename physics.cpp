#include "physics.h"
#include "body.h"

#include <iostream>

const double MINIMUM_MAGNITUDE = 4.0;

namespace physics {
    void evolve(std::vector<Body*>& v, CollisionMode mode);
    void resolveCollisions(std::vector<Body*>& v, CollisionMode mode);
    void collideElastic(std::vector<Body*>& v);
    void collideInelastic(std::vector<Body*>& v);
    Vector3 getSeparationVector(Body* b1, Body* b2);
    Vector3 F_r(Body* b1, Body* b2);
    Vector3 multiply(Vector3 v, double c);
    Vector3 add(Vector3 v, Vector3 w);


    double dt = 0.01;
    double G = 10000; //0.0000000000667;

    void evolve(std::vector<Body*>& v, CollisionMode mode) {
        // insert all bodies into tree
        // iterate over all bodies and update force
        for (int i = 0; i < v.size(); i++) {
            //
        }
    }

    void resolveCollisions(std::vector<Body*>& v, CollisionMode mode) {
        if (mode == CollisionMode::Elastic) {
            collideElastic(v);
        } else if (mode == CollisionMode::Inelastic) {
            collideInelastic(v);
        }
    }

    void collideElastic(std::vector<Body*>& v) {
        for (int i = 0; i < v.size() - 1; i++) {
            for (int j = i + 1; j < v.size(); j++) {
                Vector3 r = getSeparationVector(v[i], v[j]);

                if (r.magnitude() < 0.8) { // TODO: make this not a magic number
                    double mu = v[i]->_mass + v[j]->_mass;

                    double a = (v[i]->_mass - v[j]->_mass) / mu;
                    double b = 2 * v[j]->_mass / mu;
                    double c = 2 * v[i]->_mass / mu;
                    double d = -1 * a;

                    Vector3 v1 = add(multiply(v[i]->_velocity, a), multiply(v[j]->_velocity, b));
                    Vector3 v2 = add(multiply(v[i]->_velocity, c), multiply(v[j]->_velocity, d));

                    v[i]->_velocity.set(v1.x, v1.y, v1.z);
                    v[j]->_velocity.set(v2.x, v2.y, v2.z);
                }
            }
        }
    }

    void collideInelastic(std::vector<Body*>& v) {
        for (int i = 0; i < v.size() - 1; i++) {
            for (int j = i + 1; j < v.size(); j++) {
                Vector3 r = getSeparationVector(v[i], v[j]);

                if (r.magnitude() < 0.8) { // TODO: make this not a magic number
                    // NOTE: The procedure below is very hacky! Change later!
                    
                    double mu = 1 / (v[i]->_mass + v[j]->_mass);
                    Vector3 vNew = add(multiply(v[i]->_velocity, v[i]->_mass), multiply(v[j]->_velocity, v[j]->_mass));

                    v[i]->_velocity.set(vNew.x, vNew.y, vNew.z);
                    v[i]->_velocity.scale(mu);
                    v[i]->_mass += v[j]->_mass;

                    v[j]->_position.set(10000, 100000, 100000);
                    v[j]->_mass = 0;
                }
            }
        }
    }

    //
    // Helper functions
    //

    Vector3 getSeparationVector(Body* b1, Body* b2)
    {
        return Vector3::difference(b1->_position, b2->_position);
    }

    // F_r(r) = r / |r|^3
    Vector3 F_r(Body* b1, Body* b2)
    {
        Vector3 r = getSeparationVector(b1, b2);

        // x = 1 / |r|^3
        double mag =  1 / std::pow(std::max(r.magnitude(), MINIMUM_MAGNITUDE), 3);

        r.scale(mag);

        return r;
    }

    Vector3 multiply(Vector3 v, double c) {
        Vector3 res;

        res.set(v.x, v.y, v.z);
        res.scale(c);

        return res;
    }

    Vector3 add(Vector3 v, Vector3 w) {
        Vector3 res;

        res.set(v.x, v.y, v.z);
        res.add(w);

        return res;
    }
}
