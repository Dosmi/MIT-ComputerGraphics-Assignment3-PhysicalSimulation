#ifndef PENDULUMSYSTEM_H
#define PENDULUMSYSTEM_H

#include <vecmath.h>
#include <vector>
#include <GL/glut.h>

#include "particleSystem.h"

class PendulumSystem: public ParticleSystem
{
public:
	/* ------------------------------ constructor ------------------------------ */
		PendulumSystem(); // default
		PendulumSystem(int numParticles);


	/* ---------------------------- default methods ---------------------------- */
		// get derivative of state:
		vector<Vector3f> evalF(vector<Vector3f> state);
		// draw the particles of m_vVecState:
		void draw();

	/* -------------------------- additional_methods --------------------------- */
    // method to collect state info (position&speed) from all particles:
		vector<Vector3f> collectSystemState();

};

#endif
