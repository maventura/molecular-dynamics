#include "atom.h"

atom::atom() {
    this->speed = vector3df(0, 0, 0);
    this->mass = 0.1;

}

atom::~atom() {
    //dtor
}

atom *newAtom(double x, double y, double z, int elem) {
    atom *a = new atom;
    a->elem = elem;
    a->teleport(vector3df(x, y, z));
    return a;
}
