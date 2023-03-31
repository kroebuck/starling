#include "physics.h"

const double MINIMUM_MAGNITUDE = 4.0;

Vector3 getSeparationVector(Particle* p1, Particle* p2);
Vector3 F_r(Particle* p1, Particle* p2);

namespace physics {
    double dt = 0.01;
    double G = 100000.0;

    void update(std::vector<Particle*>& p, CollisionMode mode) {
        if (mode == CollisionMode::Collisionless) {
            //
        }

        // update velocity/position & reset da to zero
        for (int i = 0; i < p.size(); i++) {
            p[i]->velocity.add(p[i]->acceleration, dt / 2.0);
            p[i]->position.add(p[i]->velocity, dt);
            p[i]->acceleration.scale(0.0);
        }

        // calculate gravitational acceleration b/w all pairs of bodies
        for (int i = 0; i < p.size() - 1; i++) {
            for (int j = i + 1; j < p.size(); j++) {
                Vector3 r = F_r(p[i], p[j]);   // r = r / |r|^3

                p[i]->acceleration.add(r, p[j]->mass);
                p[j]->acceleration.add(r, -1 * p[i]->mass);
            }
        }

        // update velocity of each body
        for (int i = 0; i < p.size(); i++) {
            p[i]->velocity.add(p[i]->acceleration, G * dt / 2.0);
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
