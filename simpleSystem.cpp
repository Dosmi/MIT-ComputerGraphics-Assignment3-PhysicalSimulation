
#include "simpleSystem.h"
#include <iostream>

using namespace std;

SimpleSystem::SimpleSystem()
{ //@Class constructor
	m_numParticles = 1;
	Vector3f init(1.0);// = Vector3f( 0.0, 0.0, 0.0 );
	// add the initial vector to the data structure
	vector<Vector3f> state_vector;
	state_vector.push_back(init);
	// and set it as the initial state vector for the system
	this->setState(state_vector);
}

// for a given state, evaluate f(X,t)
vector<Vector3f> SimpleSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;
	for (unsigned int i = 0; i < state.size(); i++)
	{
		// right handside of this simple system is (-y, x, 0)
		f.push_back( Vector3f(-1*state[i][1], state[i][0], 0.f) );
	}
	dbug "" eol;

	return f;
}

// render the system (ie draw the particles)
void SimpleSystem::draw()
{		// note, since SimpleSystem inherits from ParticleSystem,
	  // ... we can access the protected 'm_vVecState'
		for (unsigned int i = 0; i < m_vVecState.size(); i++)
		{
			Vector3f pos = m_vVecState[i];//YOUR PARTICLE POSITION
			dbug logvar(pos.getprint()) eol;

			glPushMatrix();
			glTranslatef(pos[0], pos[1], pos[2] );
			glutSolidSphere(0.075f,10.0f,10.0f);
			glPopMatrix();
		}
}
