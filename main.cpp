#include "materialSys.h"


bool keys[irr::KEY_KEY_CODES_COUNT];

class MyEventReceiver : public IEventReceiver {
public:
    virtual bool OnEvent(const SEvent &event) {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
            keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
            return false;
        }
        return false;
    }
};

void plotMatrix(vector< vector< float> > f, ISceneManager *smgr, IVideoDriver *driver){
     float x = 0;
     float y = 0;
     unsigned int i = 0;
     unsigned int j = 0;
     float max = -60000;
     float min = 999999999;
     vector3df locate = vector3df(f.size()/2, f.size()/2, f.size()/2);
    while(i < f.size()-1){
         while (j < f[0].size()-1){
              if(f[i][j] > max) max = f[i][j];
              if(f[i][j] < min) min = f[i][j];

              j++;
         }
         i++;
    }
    max  = 20;
     while(y < f.size()-1){
         while (x < f[0].size()-1){
             float val = f[x][y];
             float hiColor = fabs(val - min)/fabs(max-min);
             hiColor *= 254;
             driver->draw3DLine(vector3df(x,f[x][y],y) - locate,vector3df(x+1,f[x+1][y],y)- locate, SColor( 255, hiColor-1, 0,255 - hiColor +1));//alpha red green blue
             driver->draw3DLine(vector3df(x,f[x][y],y)- locate,vector3df(x,f[x][y+1],y+1)- locate,SColor( 255, hiColor-1, 0,255 - hiColor+1) );
             x += 1;
         }
         y += 1;
         x = 0;
    }
}
void plotSphericalHarmonic(IVideoDriver *driver, float t, vector3df offset, float spaceRadius, float s){
    float pi = 3.141592653589793238462643;
    float r = spaceRadius;
    float phi = 0;
    float phiMax = pi;
    float theta = 0;
    float thetaMax = 2*pi;
    while(phi < phiMax){
        while(theta < thetaMax){
                r = 80*sqrt(162/4/pi)/16 * (35*pow(cos(phi),4)/3-10*pow(cos(phi),2)+1);
                r *= (cos(5*t)*sin(3*t)+20)/25;

                vector3df pos1;
                pos1.X=r*sin(phi)*cos(theta);
                pos1.Y=r*sin(phi)*sin(theta);
                pos1.Z=r*cos(phi);

                r = 80*sqrt(162/4/pi)/16 * (35*pow(cos(phi+s),4)/3-10*pow(cos(phi+s),2)+1);
                r *= (cos(5*t)*sin(3*t)+20)/25;
                vector3df pos2;
                pos2.X=r*sin(phi+s)*cos(theta);
                pos2.Y=r*sin(phi+s)*sin(theta);
                pos2.Z=r*cos(phi+s);
                r = 80*sqrt(162/4/pi)/16 * (35*pow(cos(phi),4)/3-10*pow(cos(phi),2)+1);
                r *= (cos(5*t)*sin(3*t)+20)/25;

                vector3df pos3;
                pos3.X=r*sin(phi)*cos(theta+s);
                pos3.Y=r*sin(phi)*sin(theta+s);
                pos3.Z=r*cos(phi);

                pos1 += offset;
                pos2 += offset;
                pos3 += offset;

                driver->draw3DLine(pos1, pos2);
                driver->draw3DLine(pos1, pos3);



                theta += s;
        }
        phi += s;
        theta = 0;
    }
}

void plotSpherical(IVideoDriver *driver, float t, vector3df offset, float spaceRadius, float s){
    float pi = 3.141592653589793238462643;
    float r = spaceRadius;
    float phi = 0;
    float phiMax = pi;
    float theta = 0;
    float thetaMax = 2*pi;
    while(phi < phiMax){
        while(theta < thetaMax){

                vector3df pos1;
                pos1.X=r*sin(phi)*cos(theta);
                pos1.Y=r*sin(phi)*sin(theta);
                pos1.Z=r*cos(phi);
                pos1 += offset;

                vector3df pos2;
                pos2.X=r*sin(phi+s)*cos(theta);
                pos2.Y=r*sin(phi+s)*sin(theta);
                pos2.Z=r*cos(phi+s);
                pos2 += offset;

                vector3df pos3;
                pos3.X=r*sin(phi)*cos(theta+s);
                pos3.Y=r*sin(phi)*sin(theta+s);
                pos3.Z=r*cos(phi);
                pos3 += offset;

                driver->draw3DLine(pos1, pos2,SColor( 0.02, 200, 200,200));
                driver->draw3DLine(pos1, pos3,SColor( 0.02, 200, 200,200));



                theta += s;
        }
        phi += s;
        theta = 0;
    }
}


    int main() {


for(int a = 1; a < 4; ++a){
        int a18 = a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a;
int a86 = a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a;
    if((43*215*3*a18 - 5*215*5*a86 + 5*43*12*a)%46225 == 0) cout << a << endl;
}
    bool md = false;
    int totalAtoms = 8*8*8; //if 3dCube, this value should be the cube of an integer.
    float spaceRadius = 800;
    int rowSize = (int)pow(totalAtoms, 1.0 / 3);
    float forceDistance = 800 * 800; //If the sqNorm used in materialSys.cpp, this should be the square of the distance.
    float atomGridDist = 40.0;
    float camSpeed = 4.0;
    float step = 0.02;
    float t = 0;
    float limX = 500;
    float limY = 500;
    float limZ = 500;
    //It's for caltulating a lot of movements before showing them, but it doesnt increase performance notably.
    long long int itersPerShow =1;
    long long int iters = 0;
    materialSys ms;
    ms.itersForNeighborUp = 0;//keep at 0.
    ms.maxItersForNeighborUp = 20; //iterations until neighbors are updated.
    //Setting a seed for generating random numbers
    srand(time(NULL));
    //Setting the stage.
    //Creating an event reciever for managinr the keyboard, mouse and such.
    MyEventReceiver rv;

    // create a NULL device to detect screen resolution
    IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);
    core::dimension2d<u32> deskres =
        nulldevice->getVideoModeList()->getDesktopResolution();
    nulldevice -> drop();
    // now the dimensions can be used to create the real device
    IrrlichtDevice *device = createDevice(EDT_OPENGL, deskres, 32, true, false,
                                          true, &rv);
    //    IrrlichtDevice *device = createDevice(EDT_OPENGL);
    IVideoDriver *driver = device->getVideoDriver();
    ISceneManager *smgr = device->getSceneManager();
    device->getCursorControl()->setVisible(false);
    IGUIEnvironment* guienv = device->getGUIEnvironment();
    smgr->setAmbientLight(video::SColorf(0.3,0.3,0.3,1));
    ILightSceneNode* lightUp = smgr->addLightSceneNode( 0, core::vector3df(0,4000,2000), video::SColorf(0.1,0.1,0.1), 8000, 1 );
    ILightSceneNode* lightSide = smgr->addLightSceneNode( 0, core::vector3df(-20000,-20000,-20000), video::SColorf(0.1,0.1,0.1), 18000, 1 );

    guienv->addStaticText(L"MOVEMENT: W = FRONT, S = BACK, A = LEFT, D = RIGHT, Q = UP, Z = DOWN, V = nxt elem, B = prev elem", rect<int>(10,10,600,40), true);
    guienv->addStaticText(L"CONTROL: T = STOP MOTIONS, R = RESET SPEED AND POSITION, Y = ADD RANDOM SPEED, H = LARGER STEP, J = SMALLER STEP", rect<int>(10,50,600,80), true);
    device->setEventReceiver(&rv);
    //Setting an array for key pressing
    for (int x = 0; x < irr::KEY_KEY_CODES_COUNT; x++) { keys[x] = false; }
    //Creating examples of 3D object


    ISceneNode *backPoint = smgr->addSphereSceneNode(1, 1);
    backPoint->setPosition(vector3df(0, 0, -1));

    vector3df basePos = vector3df(999,999,999);

    //BUILDING THE PARTICLES
    int residueSize = totalAtoms;
    residue *molecule = new residue;
    buildResidue(molecule, &ms, smgr, driver, residueSize, totalAtoms, basePos);

    //CREATE CAMERA
    ICameraSceneNode *cam = smgr->addCameraSceneNodeFPS();
    //CREATE CAMERA BACKPOINT TO CALCULATE VISION ROTATION.
    backPoint->setParent(
        cam); //sphere's position is always behind the camera.
    //SET SKYBOX.
    ISceneNode *SkyBox = smgr->addSkyBoxSceneNode(
                             driver->getTexture("background.jpg"),
                             driver->getTexture("background.jpg"),
                             driver->getTexture("background.jpg"),
                             driver->getTexture("background.jpg"),
                             driver->getTexture("background.jpg"),
                             driver->getTexture("background.jpg"));

//LastPos vector is used to center (a little) the collection of atoms.
vector3df lastPos = vector3df(atomGridDist * rowSize , atomGridDist * rowSize , atomGridDist * rowSize);
    for (int i = 0; i <  rowSize; ++i) {
        for (int j = 0; j <  rowSize; ++j) {
            for (int k = 0; k <  rowSize; ++k) {
                ms.atoms[rowSize * rowSize * i + rowSize * j + k]->teleport(vector3df(atomGridDist * i ,
                        atomGridDist * j , atomGridDist * k) - lastPos/2);
            }
        }
    }
    vector3df normal;
    int updates = 0;
    int addElem = 1;

    cam->setPosition(cam->getPosition() + vector3df(-400, 0, 0));
    //MAIN UPDATE CICLE.
    while (device->run() && device) {
        //UPDATE TIME AND CAMERA.
        t += step;
        vector3df pos = cam->getAbsolutePosition();
        vector3df target = cam->getTarget();
        normal = target - pos;
        normal.normalize();
        vector3df nearTarget = pos + normal*50;
        vector3df tangent = normal.crossProduct(vector3df(0, 1, 0));
        tangent.normalize();



        //UPDATE KEYSTROKES.
        if (keys[KEY_KEY_W]) {
            cam->setPosition(cam->getPosition() + camSpeed * normal);
        }
        if (keys[KEY_KEY_A]) {
            cam->setPosition(cam->getPosition() + camSpeed * tangent);
        }
        if (keys[KEY_KEY_S]) {
            cam->setPosition(cam->getPosition() - camSpeed * normal);
        }
        if (keys[KEY_KEY_D]) {
            cam->setPosition(cam->getPosition() - camSpeed * tangent);
        }
        if (keys[KEY_KEY_Z]) {
            cam->setPosition(cam->getPosition() + vector3df(0, -camSpeed, 0));

        }
        if (keys[KEY_KEY_Q]) {
            cam->setPosition(cam->getPosition() + vector3df(0, camSpeed, 0));

        }

        if (keys[KEY_KEY_H]) {
            step = step * 1.1;

        }

        if (keys[KEY_KEY_J]) {
            step = step * 0.9090909090909090;
        }

        if (keys[KEY_KEY_R]) {
            t = 0;
            for (int i = 0; i <  rowSize; ++i) {
                for (int j = 0; j <  rowSize; ++j) {
                    for (int k = 0; k <  rowSize; ++k) {
                ms.atoms[rowSize * rowSize * i + rowSize * j + k]->teleport(vector3df(atomGridDist * i ,
                        atomGridDist * j , atomGridDist * k) - lastPos/2);
                        ms.atoms[rowSize * rowSize * i + rowSize * j + k]->speed = vector3df(0, 0,
                                0); //rand(-0.01, 0.01);
                    }
                }
            }
        }


        if (keys[KEY_KEY_T]) {

            for (int i = 0; i <  rowSize; ++i) {
                for (int j = 0; j <  rowSize; ++j) {
                    for (int k = 0; k <  rowSize; ++k) {
                        ms.atoms[rowSize * rowSize * i + rowSize * j + k]->speed = vector3df(0, 0,
                                0); //rand(-0.01, 0.01);

                    }
                }
            }
        }


        if (keys[KEY_KEY_Y]) {

            for (int i = 0; i <  rowSize; ++i) {
                for (int j = 0; j <  rowSize; ++j) {
                    for (int k = 0; k <  rowSize; ++k) {
                        ms.atoms[rowSize * rowSize * i + rowSize * j + k]->speed += vector3df(rand(-0.5,0.5), rand(-0.5, 0.5), rand(-0.5, 0.5));
                    }
                }
            }
        }

       if (keys[KEY_KEY_M]) {
            md = !md;
        }

        if ( keys[KEY_KEY_G]) {
        ms.atoms.push_back(new atom);
        totalAtoms += 1;
        ms.atoms[totalAtoms-1]->elem = addElem;
        ms.atoms[totalAtoms-1]->rmLJ = elemRadius[ms.atoms[totalAtoms-1]->elem];
        ms.atoms[totalAtoms-1]->epsilonLJ = 50.0;
        ms.cantAtoms++;
        ms.atoms[totalAtoms-1]->show(smgr);
        //        //Left speed=0;
        ms.atoms[totalAtoms-1]->speed = vector3df(0, 0, 0);//rand(-0.01, 0.01);

        ms.atoms[totalAtoms-1]->figure->setMaterialFlag(EMF_LIGHTING, false);
        ms.atoms[totalAtoms-1]->teleport(vector3df(999,999,999));

        ms.atoms[totalAtoms-1]->show(smgr);
        ms.atoms[totalAtoms-1]->teleport(nearTarget);
        ms.atoms[totalAtoms-1]->figure->setMaterialTexture(0, driver->getTexture(elemTextures[ms.atoms[totalAtoms-1]->elem]));
        ms.atoms[totalAtoms-1]->figure->setMaterialFlag(video::EMF_LIGHTING, true);
        ms.atoms[totalAtoms-1]->figure->getMaterial(0).Shininess = 20.0f;
        }
        if ( keys[KEY_KEY_V]) {
                addElem+= 1;
        }
            if ( keys[KEY_KEY_B]) {
                addElem-= 1;
        }
        //BEGUIN THE SCEENE AND DRAW OBJECTS.
        driver->beginScene(true, true, video::SColor(255, 0, 0, 255));
        smgr->drawAll();
        guienv->drawAll();


        //PLOT FUNCTION(Sometimes unused)
        float x0 = -80;
        float y0 = -80;
        float xf = 80;
        float yf = 80;
        int rangeX = (int)(xf-x0);
        int rangeY = (int)(yf-y0);
        int x, y;
        vector<vector<float> > f(rangeX);
    for ( int i = 0 ; i < rangeX ; i++ ){
       f[i].resize(rangeY);
       for(int j = 0; j < rangeY; ++j){
            x = i+ x0;
            y = j + y0;
        //uncomment to plot. (WARNING: Sometimes it uses atoms positions, can lead to a segmentation fault.
       // f[i][j] = x*x - y*y;

       }
    }   //PARTICLES UPDATE FUNCTION.
        update(ms, smgr, driver, step, itersPerShow, iters, forceDistance, limX, limY, limZ, f, spaceRadius, molecule, md);
        updates++;
        //PLOT 3D CARTESIAN
        // plotMatrix(f, smgr, driver);

        //PLOT 3D SPHERICAL (currently used to plot charges of particles)
        for(int i = 0; i < totalAtoms; i++){
            if(ms.atoms[i]->charge > 0){
                plotSpherical(driver, t, ms.atoms[i]->pos , elemRadius[ms.atoms[i]->elem]/12 + ms.atoms[i]->charge, 0.6283);
            }
        }
        //plotSpherical(driver, t,vector3df(0,0,0), spaceRadius, 0.2);

        //DRAW BIG BOX
        driver->draw3DLine(vector3df(limX, limZ, limY),vector3df(-limX, limZ, limY));
        driver->draw3DLine(vector3df(limX, limZ, limY),vector3df(limX, -limZ, limY));
        driver->draw3DLine(vector3df(limX, limZ, limY),vector3df(limX, limZ, -limY));
        driver->draw3DLine(vector3df(-limX, -limZ, -limY),vector3df(limX, -limZ, -limY));
        driver->draw3DLine(vector3df(-limX, -limZ, -limY),vector3df(-limX, -limZ, limY));
        driver->draw3DLine(vector3df(-limX, -limZ, -limY),vector3df(-limX, limZ, -limY));
        driver->draw3DLine(vector3df(-limX, limZ, limY),vector3df(-limX, -limZ, limY));
        driver->draw3DLine(vector3df(-limX, limZ, limY),vector3df(-limX, limZ, -limY));
        driver->draw3DLine(vector3df(limX, -limZ, -limY),vector3df(limX, -limZ, limY));
        driver->draw3DLine(vector3df(limX, -limZ, -limY),vector3df(limX, limZ, -limY));
        driver->draw3DLine(vector3df(-limX, -limZ, limY),vector3df(limX, -limZ, limY));




        matrix4 mat;
        SMaterial m;
        m.Lighting=false;
        driver->setMaterial(m);
        driver->setTransform(video::ETS_WORLD, mat);
//   driver->draw3DLine(vector3df(0,0,0),vector3df(0,40,0));
//   driver->draw3DLine(vector3df(0,0,0),vector3df(0,0,40));





        //End the sceene
        driver->endScene();
    }
}
