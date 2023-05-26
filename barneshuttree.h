#ifndef BARNESHUTTREE_H
#define BARNESHUTTREE_H

#include "body.h"
#include "octant.h"
#include "vector3.h"

class BarnesHutTree {
public:
    Body* _body;
    Octant* _octant;
    BarnesHutTree* _children[8];

    BarnesHutTree(Octant* o);
    void insert(Body* b);
    void updateForce(Body* b);
    bool isExternal();
    int getChildOctantIndex(Vector3 point);
    Octant* generateChildOctant(int index);
};

#endif