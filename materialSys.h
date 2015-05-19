#ifndef MATERIALSYS_H
#define MATERIALSYS_H
#include "atom.h"

class materialSys {
public:
    //float boxRad;
    //float cellNumber;
    int itersForNeighborUp; //iterations until the neighbors of an atom are updated
    int maxItersForNeighborUp; //iterations until the neighbors of an atom are updated
    int cantAtoms;
    //vector< vector< vector< vector< int > > > > atomsPerCell
    vector<atom *> atoms;
    materialSys();
    ~materialSys();
    void addAtom(atom *a) {
        this->atoms.push_back(a);
    }
protected:
private:
};

//METHODS
void oldDynamics(materialSys ms, float step, residue molecule, IVideoDriver *driver, int atoms, float limX, float limY, float limZ);
void amberDynamics(materialSys ms, float step, residue molecule, IVideoDriver *driver, int atoms, float limX, float limY, float limZ);
void steepestDescent(materialSys ms, float step, residue molecule, IVideoDriver *driver, int atoms, float limX, float limY, float limZ);

void update(materialSys &ms, ISceneManager *smgr, IVideoDriver *driver, float step, long long int itersPerShow, long long int iters,
            float forceDistance, float limX, float limY, float limZ, vector<vector<float> > &densityMatrix, float spaceRadius, residue *molecule, bool md);

//STRUCTURE
void makeBond(materialSys ms, int i, int j);
void makeHBond(materialSys ms, int i, int j);
bool sameResidue(const atom *a2, const atom *a1);
bool hBondAble(const atom *a1, const atom *a2);
void buildResidue(residue *molecule, materialSys *ms, ISceneManager *smgr, IVideoDriver *driver, int size, int totalAtoms, vector3df basePos);

//MATH
vector3df calculateForce(const atom *a1, const atom *a2, float step, float epsilon, float rm, residue *molecule, materialSys &ms, IVideoDriver *driver);
float manhattanNorm(atom *a1, atom *a2);
float norm2(atom *a1, atom *a2);
float sqNorm(vector3df v1, vector3df v2);
bool inRange(vector3df pos, float limX, float limY, float limZ);

//FORCES
vector3df torsionForce(const atom *a1,const  atom *a2,const  atom *a3, const  atom *a4);
vector3df angularForce(const atom *a1,const  atom *a2,const  atom *a3);
vector3df cuadraticForce(vector3df v1, vector3df v2, float step, float epsilon, float rm);
vector3df electricForce(const atom *a1,const atom *a2);
vector3df hBondForce(const atom *a1,const atom *a2, float step, float epsilon, float rm);
vector3df lennardJonesForce(vector3df v1, vector3df v2, float step, float epsilon, float rm);
vector3df elasticForce(vector3df v1, vector3df v2, float step,float k, float l);
float gaussianPotential(float epsilon, float rm, float r);


#endif // MATERIALSYS_H
