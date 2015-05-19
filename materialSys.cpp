#include "materialSys.h"

materialSys::materialSys() {
    //ctor
}

materialSys::~materialSys() {
    //dtor
}




void buildResidue(residue *molecule, materialSys *ms, ISceneManager *smgr, IVideoDriver *driver, int size, int totalAtoms, vector3df basePos){
   int i = 0;
    molecule -> resId = 0;
    for (i = 0; i < size; i++) {
        ms->atoms.push_back(new atom);
    }
    for (i = 0; i < size; i++) {
        ms->atoms[i]->elem = 6;
        ms->atoms[i]->id = i;
        ms->atoms[i]->res = molecule;
        ms->atoms[i]->charge = 0;//pow(-1,i);
        if(i > 0 && i%8 == 7){
//              ms->atoms[i]->elem = 8;
//              ms->atoms[i]->charge = 5;//pow(-1,i);
                makeBond(*ms, i-7, i-6);
                makeBond(*ms, i-6, i-5);
                makeBond(*ms, i-5, i-4);
                makeBond(*ms, i-4, i-3);
                makeBond(*ms, i-3, i-2);
                makeBond(*ms, i-2, i-1);
                makeBond(*ms, i-1, i);




        }
      //  if(i > 5 && i < 7){ makeHBond(ms, i, i+1);}// anda mal
        ms->atoms[i]->rmLJ = elemRadius[ms->atoms[i]->elem];
        ms->atoms[i]->epsilonLJ = 25;
        ms->cantAtoms++;
        ms->atoms[i]->show(smgr);
        //        //Left speed=0;
        ms->atoms[i]->speed = vector3df(0, 0, 0);//rand(-0.01, 0.01);
        ms->atoms[i]->accel = vector3df(0, 0, 0);//rand(-0.01, 0.01);
        ms->atoms[i]->halfStepSpeed = vector3df(0, 0, 0);//rand(-0.01, 0.01);



        ms->atoms[i]->figure->setMaterialFlag(EMF_LIGHTING, true);
        ms->atoms[i]->teleport(vector3df(0, 0, 9999));

        ms->atoms[i]->show(smgr);

        ms->atoms[i]->figure->setMaterialTexture(0, driver->getTexture(elemTextures[ms->atoms[i]->elem]));
        ms->atoms[i]->figure->setMaterialFlag(EMF_LIGHTING, true);
        ms->atoms[i]->figure->getMaterial(0).Shininess = 20.0f;
       // ms->atoms[i]->figure->getMaterial(0).AmbientColor.set(255,255,255,255);
       // ms->atoms[i]->figure->getMaterial(0).DiffuseColor.set(222,255,255,255);
        ms->atoms[i]->figure->getMaterial(0).EmissiveColor.set(20,20,20,20);
    }
}




void makeBond(materialSys ms, int i, int j){
ms.atoms[i]->bonds.push_back(j);
ms.atoms[j]->bonds.push_back(i);
}

void makeHBond(materialSys ms, int i, int j){
ms.atoms[i]->hBonds.push_back(j);
ms.atoms[j]->hBonds.push_back(i);
}

bool sameResidue(const atom *a2, const atom *a1){
return a1->res->resId == a2->res->resId;
}
bool hBondAble(const atom *a1, const atom *a2){
 return (a1->elem == 1 && (a2->elem == 7 || a2->elem == 8 || a2->elem == 9)) || (a2->elem == 1 && (a1->elem == 7 || a1->elem == 8 || a1->elem == 9));
}

float lennardJonesPotential(float epsilon, float rm, float r) {
    float term = pow(rm / r, 6);
    return epsilon * (pow(term, 2) - 2 * term);
}
float gaussianPotential(float epsilon, float rm, float r){
return 0.5*epsilon*pow(2.71828,(-pow(r-3*rm,2))); //el 0.5 es para que el potencial a superar(3 veces mas lejos) sea menor al potencial de union.
}
vector3df cuadraticForce(vector3df v1, vector3df v2, float step, float epsilon, float rm) {
   vector3df dir = v2 - v1;
    float r = (v2 - v1).getLength(); //r is the distance between the particles
   // float epsilon = 50;//epsilon is the minimun of the potential
   //float rm = 15.0; //rm is where the potential reaches its minimum
    dir.normalize();
    float force = pow(r,2);
    force = force / step;
    return force * dir;
}

vector3df lennardJonesForce(vector3df v1, vector3df v2, float step, float epsilon, float rm) {
    vector3df dir = v2 - v1;
    float r = dir.getLength(); //r is the distance between the particles
   // float epsilon = 50;//epsilon is the minimun of the potential
   //float rm = 15.0; //rm is where the potential reaches its minimum
    dir.normalize();
  //  float force = lennardJonesPotential(epsilon, rm, r + step) - lennardJonesPotential(epsilon, rm, r);
  float rm6 = pow(rm,6);
  float r6 = pow(r,6);
  float force = -(12*rm6*(rm6-r6))/(r*pow(r6,2));
    return force * dir;
}
//Lennard Jones and Gaussian force
vector3df ljgForce(vector3df v1, vector3df v2, float step, float epsilon, float rm) {
    vector3df dir = v2 - v1;
    float r = dir.getLength(); //r is the distance between the particles
   // float epsilon = 50;//epsilon is the minimun of the potential
   //float rm = 15.0; //rm is where the potential reaches its minimum
    dir.normalize();
    float force =
    lennardJonesPotential(epsilon, rm, r + step)
    - lennardJonesPotential(epsilon, rm, r)
    +    gaussianPotential(epsilon, rm, r + step)
    -gaussianPotential(epsilon, rm, r);

    force = force / step;
    return force * dir;
}


vector3df elasticForce(vector3df v1, vector3df v2, float step, float k, float l) {
    vector3df dir = v2 - v1;
    float x = (v2 - v1).getLength();
    dir.normalize();
    float force = k * (x - l);
    return force * dir;
}

float manhattanNorm(vector3df a1, vector3df a2) {
    return fabs(a1.X - a2.X) + fabs(a1.Y - a2.Y) + fabs(a1.Z - a2.Z);
}

float norm2(vector3df v1, vector3df v2) {
    return (v1 - v2).getLength();
}

float sqNorm(vector3df v1, vector3df v2) {
    return (v1 - v2).getLengthSQ();
}

bool inRange(vector3df pos, float limX, float limY, float limZ){
return (pos.X < limX && pos.X > -limX) && (pos.Y < limY && pos.Y > -limY) && (pos.Z < limZ && pos.Z > -limZ);
}

vector3df electricForce(const atom *a1,const atom *a2){
    float epsilonZero = 1;
    vector3df a1pos = a1->pos;
    vector3df a2pos = a2->pos;
    vector3df dir = a2pos - a1pos;
    float r = dir.getLength();
    dir.normalize();
return -dir*(a1->charge*a2->charge)/(epsilonZero*r); //deberia ir epsilon
}


vector3df hBondForce(const atom *a1,const atom *a2, float step, float c, float d) {
    vector3df v1 = a1->pos;
    vector3df v2 = a2->pos;
    vector3df dir = v2 - v1;
    float r = dir.getLength(); //r is the distance between the particles
    dir.normalize();

  float force = -12*c/pow(r,13) + 10*d/pow(r,11);
    return force * dir;
}

vector3df angularForce(const atom *a1,const  atom *a2,const  atom *a3){
    vector3df v1 = a1->pos - a2->pos;
    vector3df v2 = a3->pos - a2->pos;
    float k = 0.1;
    float tita0 = 110;
    float tita = (180/3.1415)*acos(v1.dotProduct(v2)/(v1.getLength()*v2.getLength()));
    vector3df dir = v2 - cos(tita*3.1415/180)*v2.getLength()*(v1/v1.getLength());
    dir.normalize();
    vector3df force = dir*k*(tita - tita0);

    return force;
}
vector3df torsionForce(const atom *a1,const  atom *a2,const  atom *a3, const  atom *a4){
    vector3df a4sft = a4->pos - (a3->pos - a2->pos);

    vector3df v1 = a1->pos - a2->pos;
    vector3df v2 = a4sft - a2->pos;
    float k = 0.1;
    float tita0 = 180;
    float tita = (180/3.1415)*acos(0.9999999*v1.dotProduct(v2)/((v1.getLength()*v2.getLength())));
    vector3df dir = v2 - cos(tita*3.1415/180)*v2.getLength()*(v1/v1.getLength());
    dir.normalize();
    vector3df force = dir*k*(tita - tita0);
    return force;
}
vector3df calculateForce(const atom *a1, const atom *a2, float step, float epsilon, float rm, residue *molecule, materialSys &ms, IVideoDriver *driver) {
    vector3df force = vector3df(0,0,0);

    if(!in(a2->id, a1->bonds)){
        force += lennardJonesForce(a1->pos, a2->pos, step, epsilon, rm);
    }
    if(!in(a2->id, a1->bonds)){
        force += 30*electricForce(a1,a2);
    }
    if(in(a2->id, a1->bonds)){
        force += elasticForce(a1->pos, a2->pos, step,a1->epsilonLJ/3, a1->rmLJ );
        for(unsigned int i = 0; i < a2->bonds.size(); ++i){ //Los vecinos unidos a a1 y sus uniones.
            atom *a3 = ms.atoms[a2->bonds[i]];
            if(a3->id != a1->id){
                force += angularForce(a1, a2, a3);
                //driver->draw3DLine(a1->pos, a1->pos + 20*angularForce(a1, a2, a3));

            }

            for(unsigned int j = 0; j < a3->bonds.size(); ++j){
                atom *a4 = ms.atoms[a3->bonds[j]];
                if(a4->id != a1->id && a4->id != a2->id && a4->id != a3->id
                   && a3->id != a2->id && a3->id != a1->id && a2->id != a1->id){
                    force += torsionForce(a1, a2, a3, a4);
                    //driver->draw3DLine(a1->pos, a1->pos + 20*torsionForce(a1, a2, a3, a4));


                }

            }
        }
    }

        if(in(a2->id, a1->hBonds)){
            float c = 25*10;
            float d = 25*10;
            force += hBondForce(a1, a2, step, c, d);
    }

    return force;
}
//MAIN UPDATE FUNCTION
void update(materialSys &ms, ISceneManager *smgr, IVideoDriver *driver,
            float step,  long long int itersPerShow,  long long int iters,
            float forceDistance, float limX, float limY, float limZ, vector<vector<float> > &densityMatrix,
             float spaceRadius, residue *molecule, bool md) {

    int atoms = ms.atoms.size();
    long long int currentIters = 0;

    std::vector< vector3df > oldPos;

    for (int i = 0; i < atoms; i++) {
        oldPos.push_back(ms.atoms[i]->pos);

    }
    //Preparing to show lines
     matrix4 mat;
   SMaterial m;
   m.Lighting=false;
   driver->setMaterial(m);
   driver->setTransform(video::ETS_WORLD, mat);
   //main while cicle.

       //UPDATE POSITIONS.
    for (int i = 0; i < atoms; ++i) {
        ms.atoms[i]->halfStepSpeed = ms.atoms[i]->speed + 0.5*ms.atoms[i]->accel*step;
        ms.atoms[i]->pos += ms.atoms[i]->halfStepSpeed*step;
        ms.atoms[i]->teleport(ms.atoms[i]->pos);

    }//End update positions
    while (currentIters < itersPerShow) {
        currentIters++;
        //UPDATE NEIGHTBORS
            ms.itersForNeighborUp--;
    if(ms.itersForNeighborUp <= 0){
        for (int i = 0; i < atoms; ++i) {
                ms.atoms[i]->neighbors.clear();
                atom *a1 = ms.atoms[i];
                vector3df a1pos = a1->pos;
            for (int j = 0; j < atoms; ++j) {
                if (i != j && sqNorm(a1pos, ms.atoms[j]->pos) < 100*elemRadius[ms.atoms[j]->elem] + 100*elemRadius[a1->elem]) {
                        a1->neighbors.push_back(j); //id = position in ms.atoms.
                }
            }
        }
        ms.itersForNeighborUp = ms.maxItersForNeighborUp;
    }
    if(md){
         amberDynamics( ms,  step,  *molecule,  driver,  atoms,  limX,  limY,  limZ);

    }else{
         steepestDescent( ms,  step,  *molecule,  driver,  atoms,  limX,  limY,  limZ);

    }

    }//End itersPerShow

}



void steepestDescent(materialSys ms, float step, residue molecule, IVideoDriver *driver, int atoms, float limX, float limY, float limZ){
        for (int i = 0; i < atoms; ++i) {
            vector3df forces = vector3df(0, 0, 0);
            atom *a1 = ms.atoms[i];
            vector3df a1pos = a1->pos;
            for (unsigned int f = 0; f < a1->neighbors.size(); ++f) {
                atom *a2 = ms.atoms[a1->neighbors[f]];
                vector3df a2pos = a2->pos;
                    forces += calculateForce(a1, a2, step,a1->epsilonLJ, a1->rmLJ, &molecule, ms, driver)/4;//2 por la derivada y /2 para promediar
                    forces -= calculateForce(a2, a1, step,a2->epsilonLJ, a2->rmLJ, &molecule, ms, driver)/4;
                if(in(a2->id, a1->bonds)){
                        driver->draw3DLine(a1pos, a2pos, SColor(255,0,255,0));
                    }
                if(hBondAble(a2, a1)){
                        driver->draw3DLine(a1pos, a2pos, SColor(255,255,0,0));
                    }
            }
            a1->speed = vector3df(0,0,0);
            a1->halfStepSpeed = vector3df(0,0,0);
            ms.atoms[i]->pos += step*forces;
            ms.atoms[i]->teleport(ms.atoms[i]->pos);
            if(!inRange(a1->pos, limX, limY, limZ)){
                    if(a1->pos.X < -limX || a1->pos.X > limX) a1->speed.X = -a1->speed.X;
                    if(a1->pos.Y < -limY || a1->pos.Y > limY) a1->speed.Y = -a1->speed.Y;
                    if(a1->pos.Z < -limZ || a1->pos.Z > limZ) a1->speed.Z = -a1->speed.Z;
            }
        }
}



void amberDynamics(materialSys ms, float step, residue molecule, IVideoDriver *driver, int atoms, float limX, float limY, float limZ){
        for (int i = 0; i < atoms; ++i) {
            vector3df forces = vector3df(0, 0, 0);
            atom *a1 = ms.atoms[i];
            vector3df a1pos = a1->pos;
            for (unsigned int f = 0; f < a1->neighbors.size(); ++f) {
                atom *a2 = ms.atoms[a1->neighbors[f]];
                vector3df a2pos = a2->pos;
                    forces += calculateForce(a1, a2, step,a1->epsilonLJ, a1->rmLJ, &molecule, ms, driver)/4;//2 por la derivada y /2 para promediar
                    forces -= calculateForce(a2, a1, step,a2->epsilonLJ, a2->rmLJ, &molecule, ms, driver)/4;
                if(in(a2->id, a1->bonds)){
                        driver->draw3DLine(a1pos, a2pos, SColor(255,0,255,0));
                    }
                if(hBondAble(a2, a1)){
                        driver->draw3DLine(a1pos, a2pos, SColor(255,255,0,0));
                    }
            }
            a1->accel = forces/(atomicMasses[a1->elem]);
            a1->speed = a1->halfStepSpeed + 0.5*a1->accel*step;

            if(!inRange(a1->pos, limX, limY, limZ)){
                    if(a1->pos.X < -limX || a1->pos.X > limX) a1->speed.X = -a1->speed.X;
                    if(a1->pos.Y < -limY || a1->pos.Y > limY) a1->speed.Y = -a1->speed.Y;
                    if(a1->pos.Z < -limZ || a1->pos.Z > limZ) a1->speed.Z = -a1->speed.Z;
            }
        }
}






///NOTE: NO NOT USE!!
//IT'S AN OLD DYNAMICS FUNCTION WITH COMENTED DEPRECATED CODE
//SAVED JUST AS A FORM OF BACKUP.
void oldDynamics(materialSys ms, float step, residue molecule, IVideoDriver *driver, int atoms, float limX, float limY, float limZ){

        //CALCULATE FORCES.

        for (int i = 0; i < atoms; ++i) {
            vector3df forces = vector3df(0, 0, 0);
            atom *a1 = ms.atoms[i];
            vector3df a1pos = a1->pos;

            for (unsigned int f = 0; f < a1->neighbors.size(); ++f) {
    //drawing the lines and calculating forces.
                atom *a2 = ms.atoms[a1->neighbors[f]];
                vector3df a2pos = a2->pos;
                    forces += calculateForce(a1, a2, step,a1->epsilonLJ, a1->rmLJ, &molecule, ms, driver)/4;//2 por la derivada y /2 para promediar
                    forces -= calculateForce(a2, a1, step,a2->epsilonLJ, a2->rmLJ, &molecule, ms, driver)/4;
                    if(a1->elem != 1){
                        //driver->draw3DLine(a2pos, a1pos, SColor( 255, 255, 255, 255 ) );
                    }
                if(in(a2->id, a1->bonds)){
                        driver->draw3DLine(a1pos, a2pos, SColor(255,0,255,0));
                        //if((a2pos- a1pos).getLength() > 4*(a2->rmLJ+a1->rmLJ))

                    }
                if(hBondAble(a2, a1)){
                        driver->draw3DLine(a1pos, a2pos, SColor(255,255,0,0));
                        //if((a2pos- a1pos).getLength() > 4*(a2->rmLJ+a1->rmLJ))

                    }
            //plot forces in matrix
          //  if(inRange(a1->pos, limX, limY, limZ)){
        /*   if(false && spaceRadius > norm2(a1->pos, vector3df(0,0,0))){
                    densityMatrix[int(a1pos.X) + limX][int(a1pos.Y) + limY] += 0.5*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX +1][int(a1pos.Y) + limY] += 0.4*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX][int(a1pos.Y) + limY +1] += 0.4*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX -1][int(a1pos.Y) + limY] += 0.4*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX][int(a1pos.Y) + limY -1] += 0.4*forces.getLength();

                    densityMatrix[int(a1pos.X) + limX +1][int(a1pos.Y) + limY +1] += 0.3*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX +1][int(a1pos.Y) + limY -1] += 0.3*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX -1][int(a1pos.Y) + limY +1] += 0.3*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX -1][int(a1pos.Y) + limY -1] += 0.3*forces.getLength();

                    densityMatrix[int(a1pos.X) + limX +2][int(a1pos.Y) + limY +1] += 0.2*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX +2][int(a1pos.Y) + limY -1] += 0.2*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX -2][int(a1pos.Y) + limY +1] += 0.2*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX -2][int(a1pos.Y) + limY -1] += 0.2*forces.getLength();

                    densityMatrix[int(a1pos.X) + limX +1][int(a1pos.Y) + limY +2] += 0.2*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX +1][int(a1pos.Y) + limY -2] += 0.2*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX -1][int(a1pos.Y) + limY +2] += 0.2*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX -1][int(a1pos.Y) + limY -2] += 0.2*forces.getLength();

                    densityMatrix[int(a1pos.X) + limX +2][int(a1pos.Y) + limY] += 0.2*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX -2][int(a1pos.Y) + limY] += 0.2*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX][int(a1pos.Y) + limY +2] += 0.2*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX][int(a1pos.Y) + limY -2] += 0.2*forces.getLength();

                    densityMatrix[int(a1pos.X) + limX +2][int(a1pos.Y) + limY +2] += 0.1*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX +2][int(a1pos.Y) + limY -2] += 0.1*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX -2][int(a1pos.Y) + limY +2] += 0.1*forces.getLength();
                    densityMatrix[int(a1pos.X) + limX -2][int(a1pos.Y) + limY -2] += 0.1*forces.getLength();

                }
        */
            }
            a1->accel = forces/(atomicMasses[a1->elem]);
            a1->speed = a1->halfStepSpeed + 0.5*a1->accel*step;

            if(!inRange(a1->pos, limX, limY, limZ)){
              //if(spaceRadius <= norm2(a1->pos, vector3df(0,0,0))){
                    if(a1->pos.X < -limX || a1->pos.X > limX) a1->speed.X = -a1->speed.X;
                    if(a1->pos.Y < -limY || a1->pos.Y > limY) a1->speed.Y = -a1->speed.Y;
                    if(a1->pos.Z < -limZ || a1->pos.Z > limZ) a1->speed.Z = -a1->speed.Z;



            }


        }




}
