 # 3D Molecular Dynamics Simulator

A real-time, 3D atomic and molecular dynamics simulator written in C++ using the [Irrlicht Engine](http://irrlicht.sourceforge.net/). This project visualizes particle interactions by simulating physical forces such as Lennard-Jones potentials, electrostatic repulsion/attraction, and complex bonded interactions (elastic, angular, and torsional forces) based on AMBER-like force fields.

##  Project Structure

* atom.h / atom.cpp
  Defines the "atom" class, which holds physical properties (mass, charge, speed, acceleration) and structural data (bonds, neighbors). It also includes extensive static lookup tables for atomic masses, radii, bond lengths, and visual textures for all elements.
* materialSys.h / materialSys.cpp
  The core physics engine. It maintains the system of atoms ("materialSys") and calculates intermolecular forces. It includes implementations for energy minimization ("steepestDescent") and molecular dynamics ("amberDynamics"). 
* main.cpp
  The application entry point. Initializes the Irrlicht 3D device, sets up the environment (lighting, skybox), handles user input via an event receiver, and runs the main simulation loop. It also includes experimental visualization functions for spatial density matrices and spherical harmonics.
* utils.h / utils.cpp
  General utility and helper functions for random number generation and vector lookups.

##  Key Features

* **Real-Time 3D Rendering:** Smooth visualization of atoms as 3D spheres with element-specific textures and dynamically drawn bond lines.
* **Physics Integration:** Supports both Steepest Descent (for geometry optimization) and Newtonian Molecular Dynamics.
* **Complex Force Fields:** Calculates Lennard-Jones (van der Waals), Coulombic (electrostatic), elastic (bonds), angular, and torsional forces.
* **Interactive Environment:** Fly-camera controls and real-time keyboard inputs to heat up, freeze, or reset the particle system on the fly.

##  Prerequisites

To compile and run this project, you will need:
* A C++11 compatible compiler (GCC, Clang, MSVC).
* The **Irrlicht Engine** library installed and configured in your build path.

##  Usage and Controls

Once compiled and running, you can navigate the 3D space and interact with the simulation using the following keyboard controls:

    Navigation:
    W / S : Move Forward / Backward
    A / D : Strafe Left / Right
    Q / Z : Move Up / Down
    
    Simulation Control:
    R     : Reset atom positions and set speeds to zero
    T     : Stop all atomic motion (set speeds to zero)
    Y     : Add random velocity to all atoms (simulate heating)
    H / J : Increase / Decrease the simulation time step
    M     : Toggle between Molecular Dynamics (MD) and Steepest Descent modes
    
    Element Spawning:
    G     : Spawn a new atom at the camera's target position
    V / B : Cycle Forward / Backward through the periodic table for the next spawned atom

##  Force Field Details

The simulator applies several forces to update atomic acceleration and velocity:
1.  **Lennard-Jones:** Intermolecular repulsion and dispersion (using custom $\epsilon$ and $r_m$ parameters).
2.  **Electrostatics:** Coulombic forces based on partial charges.
3.  **Elastic (Bonds):** Harmonic oscillator springs pulling bonded atoms to their equilibrium distance.
4.  **Angular:** Restoring forces for 3-body angles (e.g., keeping $110^\circ$ for sp3 carbons).
5.  **Torsional:** Dihedral angle forces for 4-body interactions.
6.  **Hydrogen Bonds:** Specialized 12-10 potential for specific electronegative interactions.
