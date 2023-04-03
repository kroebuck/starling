#include "physics.h"

#include <iostream>

const double MINIMUM_MAGNITUDE = 4.0;

namespace physics {
    void evolve(std::vector<Particle*>& p, CollisionMode mode);
    void resolveCollisions(std::vector<Particle*>& p, CollisionMode mode);
    void collideElastic(std::vector<Particle*>& p);
    void collideInelastic(std::vector<Particle*>& p);
    Vector3 getSeparationVector(Particle* p1, Particle* p2);
    Vector3 F_r(Particle* p1, Particle* p2);
    Vector3 multiply(Vector3 v, double c);
    Vector3 add(Vector3 v, Vector3 w);


    double dt = 0.01;
    double G = 100.0;

    void evolve(std::vector<Particle*>& p, CollisionMode mode) {
        // update velocity/position & reset da to zero
        for (int i = 0; i < p.size(); i++) {
            p[i]->velocity.add(p[i]->acceleration, dt / 2.0);
            p[i]->position.add(p[i]->velocity, dt);
            p[i]->acceleration.scale(0.0);
        }

        // calculate gravitational acceleration b/w all pairs of bodies
        // for (int i = 0; i < p.size() - 1; i++) {
        //     for (int j = i + 1; j < p.size(); j++) {
        //         Vector3 r = F_r(p[i], p[j]);   // r = r / |r|^3

        //         p[i]->acceleration.add(r, p[j]->mass);
        //         p[j]->acceleration.add(r, -1 * p[i]->mass);
        //     }
        // }

         resolveCollisions(p, mode);

        // update velocity of each body
        for (int i = 0; i < p.size(); i++) {
            p[i]->velocity.add(p[i]->acceleration, G * dt / 2.0);
            
            if (mode != CollisionMode::Collisionless) {
                // Temporary "walls"
                if (p[i]->position.x > 10 && p[i]->velocity.x > 0) p[i]->velocity.x *= -1;
                if (p[i]->position.x < -10 && p[i]->velocity.x < 0) p[i]->velocity.x *= -1;
                if (p[i]->position.y > 10 && p[i]->velocity.y > 0) p[i]->velocity.y *= -1;
                if (p[i]->position.y < -10 && p[i]->velocity.y < 0) p[i]->velocity.y *= -1;
                if (p[i]->position.z > 10 && p[i]->velocity.z > 0) p[i]->velocity.z *= -1;
                if (p[i]->position.z < -10 && p[i]->velocity.z < 0) p[i]->velocity.z *= -1;
            }
        }
    }

    void resolveCollisions(std::vector<Particle*>& p, CollisionMode mode) {
        if (mode == CollisionMode::Elastic) {
            collideElastic(p);
        } else if (mode == CollisionMode::Inelastic) {
            collideInelastic(p);
        }
    }

    void collideElastic(std::vector<Particle*>& p) {
        for (int i = 0; i < p.size() - 1; i++) {
            for (int j = i + 1; j < p.size(); j++) {
                Vector3 r = getSeparationVector(p[i], p[j]);

                if (r.magnitude() < 0.8) { // TODO: make this not a magic number
                    double mu = p[i]->mass + p[j]->mass;

                    double a = (p[i]->mass - p[j]->mass) / mu;
                    double b = 2 * p[j]->mass / mu;
                    double c = 2 * p[i]->mass / mu;
                    double d = -1 * a;

                    Vector3 v1 = add(multiply(p[i]->velocity, a), multiply(p[j]->velocity, b));
                    Vector3 v2 = add(multiply(p[i]->velocity, c), multiply(p[j]->velocity, d));

                    p[i]->velocity.set(v1.x, v1.y, v1.z);
                    p[j]->velocity.set(v2.x, v2.y, v2.z);
                }
            }
        }
    }

    void collideInelastic(std::vector<Particle*>& p) {
        for (int i = 0; i < p.size() - 1; i++) {
            for (int j = i + 1; j < p.size(); j++) {
                Vector3 r = getSeparationVector(p[i], p[j]);

                if (r.magnitude() < 0.8) { // TODO: make this not a magic number
                    // NOTE: The procedure below is very hacky! Change later!
                    
                    double mu = 1 / (p[i]->mass + p[j]->mass);
                    Vector3 v = add(multiply(p[i]->velocity, p[i]->mass), multiply(p[j]->velocity, p[j]->mass));

                    p[i]->velocity.set(v.x, v.y, v.z);
                    p[i]->velocity.scale(mu);
                    p[i]->mass += p[j]->mass;

                    p[j]->position.set(10000, 100000, 100000);
                    p[j]->mass = 0;
                }
            }
        }
    }

    //
    // Helper functions
    //

    Vector3 getSeparationVector(Particle* p1, Particle* p2)
    {
        Vector3 r;
        r.x = p2->position.x - p1->position.x;
        r.y = p2->position.y - p1->position.y;
        r.z = p2->position.z - p1->position.z;

        return r;
    }

    // F_r(r) = r / |r|^3
    Vector3 F_r(Particle* p1, Particle* p2)
    {
        Vector3 r = getSeparationVector(p1, p2);

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
