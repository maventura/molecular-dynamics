#ifndef ATOM_H
#define ATOM_H
#include <irrlicht.h>
#include "utils.h"


using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

static vector<float> atomicMasses = {0.0,  1.00784, 4.002602, 6.938, 9.0121831, 10.806, 12.0096, 14.00643, 15.99903, 18.998403163, 20.1797, 22.98976928
, 24.304, 26.9815385, 28.084, 30.973761998, 32.059, 35.446, 39.948, 39.0983, 40.078, 44.955908, 47.867, 50.9415
, 51.9961, 54.938044, 55.845, 58.933194, 58.6934, 63.546, 65.38, 69.723, 72.630, 74.921595, 78.971, 79.901, 83.798
, 85.4678, 87.62, 88.90584, 91.224, 92.90637, 95.95, 98, 101.07, 102.90550, 106.42, 107.8682, 112.414, 114.818, 118.710
, 121.760, 127.60, 126.90447, 131.293, 132.90545196, 137.327, 138.90547, 140.116, 140.90766, 144.242, 145, 150.36, 151.964
, 157.25, 158.92535, 162.500, 164.93033, 167.259, 168.93422, 173.054, 174.9668, 178.49, 180.94788, 183.84, 186.207, 190.23, 192.217
, 195.084, 196.966569, 200.592, 204.382, 207.2, 208.98040, 209, 210, 222, 223, 226, 227, 232.0377, 231.03588, 238.02891, 237, 244, 243
, 247, 247, 251, 252, 257, 258, 259, 262, 267, 268, 271, 272, 270, 276, 281, 280, 285, 284, 289, 288, 293, 294};

static vector<float> elemRadius = {
                0, 25, 31,145, 105, 85, 70, 65, 60, 50, 38, 180, 150, 125, 110,
                100, 100, 100, 71, 220, 180, 160, 140, 135, 140, 140, 140, 135,
                135, 135, 135, 130, 125, 115, 115, 115, 88, 235, 200, 180, 155,
                145, 145, 135, 130, 135, 140, 160, 155, 155, 145, 145, 140, 140,
                108, 260, 215, 195, 185, 185, 185, 185, 185, 185, 180, 175, 175,
                175, 175, 175, 175, 175, 155, 145, 135, 135, 130, 135, 135, 135,
                150, 190, 180, 160, 190};

static vector<io::path> iBondLengthParam = {"H","H","H","H","H","C","C","C","C","C","N","N","N","N","O",
                                            "O","O","F","F","Cl","Cl","Br","Br","I","I","P","H","H","H",
                                            "H","H","C","C","C","C","N","N","N","N","O","O","O","O","F",
                                            "F","Cl","Cl","Br","Br","I","P","S"};
static vector<io::path> jBondLengthParam = {"H","N","F","Br","P","C","O","Cl","I","S","O","Cl","I","S",
                                            "F","Br","P","F","P","Cl","P","Br","P","I","S","S","C","O",
                                            "Cl","I","S","N","F","Br","P","N","F","Br","P","O","Cl","I",
                                            "S","Cl","S","I","S","I","S","P","P","S"};

static vector<float> rij = {0.738,1.010,0.920,1.410,1.410,1.526,1.440,1.800,2.160,1.820,1.420,1.750,
                            2.120,1.690,1.410,1.790,1.640,1.406,1.500,2.031,2.040,2.337,2.240,2.836,
                            2.560,2.120,1.090,0.96,1.280,1.600,1.340,1.470,1.370,1.940,1.830,1.441,
                            1.420,1.930,1.720,1.460,1.700,2.110,1.650,1.648,1.580,2.550,2.030,2.671,
                            2.210,2.490,2.324,2.038};

static vector<float> kij = {4.661,6.057,5.600,7.301,7.257,7.643,7.347,8.241,8.859,8.117,7.526,8.266,
                            8.963,8.073,7.375,8.276,7.957,7.358,7.592,8.648,8.656,9.012,8.729,9.511,
                            9.161,8.465,6.217,5.794,6.937,7.802,7.018,7.504,7.227,8.478,8.237,7.634,
                            7.475,8.593,8.212,7.561,8.097,8.854,7.922,7.947,7.733,9.309,8.619,9.380,
                            8.728,9.058,8.805,8.316};


static vector<io::path> BondAngleParam = {"H","C", "N","O","F","Cl","Br","I","P","S"};

//static vector<float> bondAngleC = {};
//static vector<float> bondAngleC = {};



static vector<io::path> elemTextures = { "vacio",
"Hydrogen.jpg", "Helium.jpg", "Lithium.jpg", "Beryllium.jpg",
     "Boron.jpg", "Carbon.jpg", "Nitrogen.jpg", "Oxygen.jpg",
      "Fluorine.jpg", "Neon.jpg", "Sodium.jpg", "Magnesium.jpg",
       "Aluminium.jpg", "Silicon.jpg", "Phosphorus.jpg", "Sulfur.jpg",
        "Chlorine.jpg", "Argon.jpg", "Potassium.jpg", "Calcium.jpg",
         "Scandium.jpg", "Titanium.jpg", "Vanadium.jpg", "Chromium.jpg",
          "Manganese.jpg", "Iron.jpg", "Cobalt.jpg", "Nickel.jpg",
           "Copper.jpg", "Zinc.jpg", "Gallium.jpg", "Germanium.jpg",
            "Arsenic.jpg", "Selenium.jpg", "Bromine.jpg", "Krypton.jpg",
             "Rubidium.jpg", "Strontium.jpg", "Yconium.jpg", "Niobium.jpg",
              "Molybdenum.jpg", "Technetium.jpg", "Ruthenium.jpg", "Rhodium.jpg",
               "Palladium.jpg", "Silver.jpg", "Cadmium.jpg", "Indium.jpg",
                "Tin.jpg", "Antimony.jpg", "Tellurium.jpg", "Iodine.jpg",
                 "Xenon.jpg", "Cesium.jpg", "Barium.jpg", "Lanthanum.jpg",
                  "Cerium.jpg", "Praseodymium.jpg", "Neodymium.jpg", "Promethium.jpg",
                   "Samarium.jpg", "Europium.jpg", "Gadolinium.jpg", "Terbium.jpg",
                    "Dysprosium.jpg", "Holmium.jpg", "Erbium.jpg", "Thulium.jpg",
                     "Ytterbium.jpg", "Lutetium.jpg", "Hafnium.jpg", "Tantalum.jpg",
                      "Tungsten.jpg", "Rhenium.jpg", "Osmium.jpg", "Iridium.jpg",
                       "Platinum.jpg", "Gold.jpg", "Mercury.jpg", "Thallium.jpg",
                        "Lead.jpg", "Bismuth.jpg", "Polonium.jpg", "Astatine.jpg",
                         "Radon.jpg", "Francium.jpg", "Radium.jpg", "Actinium.jpg",
                          "Thorium.jpg", "Protactinium.jpg", "Uranium.jpg", "Neptunium.jpg",
                           "Plutonium.jpg", "Americium.jpg", "Curium.jpg", "Berkelium.jpg",
                            "Californium.jpg", "Einsteinium.jpg", "Fermium.jpg", "Mendelevium.jpg",
                             "Nobelium.jpg", "Lawrencium.jpg", "Rutherfordium.jpg", "Dubnium.jpg",
                              "Seaborgium.jpg", "Bohrium.jpg", "Hassium.jpg", "Meitnerium.jpg",
                               "Darmstadtium.jpg", "Roentgenium.jpg", "Copernicium.jpg", "Ununtrium.jpg",
                                "Flerovium.jpg", "Ununpentium.jpg", "Livermorium.jpg", "Ununseptium.jpg",
                                 "Ununoctium"};

static vector<io::path> amberAtomTypes = {"c","c1","c2","c3","ca","n","n1","n2","n3","n4",
                                            "na","nh","no","f","cl","br","i","o","oh","os",
                                                "s2","sh","ss","s4","s6","hc","ha","hn","ho",
                                                    "hs","hp","p2","p3","p4","p5"};

static vector<io::path> amberSpecialAtomTypes = { "vacio"};

static vector<io::path> amberDescriptions = { "sp2 C in C=O, C=S","sp1 C","sp2 C, aliphatic","sp3 C","sp2 C, aromatic",
                                            "sp2 N in amide","sp1 N","sp2 N with 2 subst.","readl double bond","sp3 N with 3 subst.",
                                            "sp3 N with 4 subst.","sp2 N with 3 subst","amine N connected o the aromatic rings","N in nitro group",
                                            "any F","any Cl","any Br","any I","sp2 O in C=O, COO-","sp3 O in hydroxyl group","sp3 O in ether and ester",
                                            "sp2 S (p=S, C=S etc)","sp3 S in thiol group","sp3 S in -SR and SS",
                                            "hypervalent S, 3 subst.","hypervalent S, 4 subst.","H on aliphatic C",
                                            "H on aromatic C","H on N","H on O","H on S","H on P","sp2 P (C=P etc)","sp3 P, 3 subst.",
                                            "hypervalent P, 3 subst.","hypervalent P, 4 subst."};
static vector<io::path> amberSpecialDescriptions = { "vacio"};


class residue{
public:
    int resId;
    vector<int> atomIds;
    vector<int> bondType;   //0 = cuadratic, 1 = ... TODO.
    vector<vector<int> > adjacencyMatrix;

protected:
private:
};
class atom {
public:
    int elem, a, e, id;
    float charge;
    residue *res;
    vector3df pos;
    vector3df speed;
    vector3df accel;
    vector3df halfStepSpeed;
    vector<int> bonds;
    vector<int> hBonds;
    vector<int> neighbors;
    double mass;
    float epsilonLJ;
    float rmLJ;
    ISceneNode *figure;
    //Constructor
    atom();
    //Destructor
    ~atom();
    //public functions

    void show(ISceneManager *smgr) {
        this->figure = smgr->addSphereSceneNode(elemRadius[this->elem]/15, 40); //6 es el minimo que queda agradable
        this->figure->setPosition(pos);
    }
    void mov(ISceneManager *smgr, vector3df disp) {

        // this->figure->setPosition(this->figure->getPosition() + vector3df(x,y,z));
        scene::ISceneNodeAnimator *anim =
            smgr->createFlyStraightAnimator(pos, pos + disp, 3500, false);
        if (anim) {
            this->figure->addAnimator(anim);
            anim->drop();
        }
        this->pos += disp;

    }


    void movFigure(ISceneManager *smgr, vector3df disp) {

        // this->figure->setPosition(this->figure->getPosition() + vector3df(x,y,z));
        scene::ISceneNodeAnimator *anim =
            smgr->createFlyStraightAnimator(pos, pos + disp, 3500, false);
        if (anim) {
            this->figure->addAnimator(anim);
            anim->drop();
        }

    }
    void teleport(vector3df p) {
        this->pos = p;
  //      if(this->elem != 1){
        this->figure->setPosition(p);}
  //  }


   void teleportWithoutShow(vector3df p) {
        this->pos = p;
}
protected:
private:
};


atom *newAtom(double x, double y, double z, int atN);
#endif // ATOM_H
