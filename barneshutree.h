#ifndef BARNESHUTREE_H
#define BARNESHUTREE_H

class BarnesHutTree {
    Particle* _particle;
    Octant* _octant;
    BarnesHutTree* _children[8];

    BarnesHutTree(Octant* o);
    void insert(Particle p);
    void updateForce(particle p);
};

#endif