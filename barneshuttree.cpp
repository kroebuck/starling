#include "barneshuttree.h"

BarnesHutTree::BarnesHutTree(Octant* o) {
    _octant = o;
    _body = NULL;
    for (int i = 0; i < 8; i++) _children[i] = NULL;
}

/*
* Insert inputted body into the Barnes-Hut tree.
* Recursively break into smaller Barnes-Hut trees such that all
* bodies are the only body contained by their octant.
*/
void BarnesHutTree::insert(Body* b) {
    if (_body == NULL) {
        _body = b;
        return;
    }
    
    // Find child octant that b will be in
    int childOctantIndex = getChildOctantIndex(b->_position);

    // Generate child octant
    if (_children[childOctantIndex] == NULL) {
        Octant* o = generateChildOctant(childOctantIndex);
        _children[childOctantIndex] = new BarnesHutTree(o);
    }

    // Insert Body b into child octant
    _children[childOctantIndex]->insert(b);

    if (isExternal()) {
        insert(b);
    } else {
        _body = Body::combine(_body, b);
    }
}

/*
* If current Barnes-Hut tree is external (no other bodies in current octant), update force using _body
* Else current octant contains multiple bodies
*   If octant's center of mass is far enough away, update force treating group of bodies as one mass
*   Else bodies in this octant should be counted individually -> recurse on child octants
*/
void BarnesHutTree::updateForce(Body* b) {
    double FAR_LIMIT = 1.0; // TODO: MOVE THIS SOMEWHERE ELSE
    if (isExternal() && _body != b) {
        b->addForce(_body);
    } else if (_octant->length() / (_body->separationVectorTo(b).magnitude()) < FAR_LIMIT) {
        b->addForce(_body);
    } else {
        for (int i = 0; i < 8; i++) {
            if (_children[i] != NULL) {
                _children[i]->updateForce(b);
            }
        }
    }
}

/*
* Checks if given BarnesHutTree is external (only body in this BarnesHutTree).
* External nodes are leaf nodes (i.e. all children octant-references are null).
*/
bool BarnesHutTree::isExternal() {
    for (int i = 0; i < 8; i++) {
        if (_children[i] != NULL) return false;
    }
    return true;
}

// z-axis | F: Front, B: Back
// y-axis | N: North, S: South
// x-axis | W: West, E: East
enum class ChildOctant {
    FNW,
    FNE,
    FSW,
    FSE,
    BNW,
    BNE,
    BSW,
    BSE
};

/* 
* 0,   1,   2,   3,   4,   5,   6,   7
* FNW, FNE, FSW, FSE, BNW, BNE, BSW, BSE
*/
int BarnesHutTree::getChildOctantIndex(Vector3 point) {
    bool front = point.x <= _octant->_position.x + _octant->length();
    bool north = point.y <= _octant->_position.y + _octant->length();
    bool east = point.z <= _octant->_position.z + _octant->length();

    return (front ? 0 : 4) + (north ? 0 : 2) + (east ? : 1);
}

Octant* BarnesHutTree::generateChildOctant(int index) {
    if (index == 0) return _octant->FNW();
    if (index == 1) return _octant->FNE();
    if (index == 2) return _octant->FSW();
    if (index == 3) return _octant->FSE();
    if (index == 4) return _octant->BNW();
    if (index == 5) return _octant->BNE();
    if (index == 6) return _octant->BSW();
    if (index == 7) return _octant->BSE();

    // should be unreachable
    return _octant->FNW();
}