#include "particleSystem.h" //  has Spring and Particle class declarations
#include "pendulumSystem.h"

const Vector3f ParticleSystem::m_root_particle_offset = Vector3f(0.f, 0.f, 0.f);

PendulumSystem::PendulumSystem()
	: ParticleSystem()
	{}

PendulumSystem::PendulumSystem(int numParticles)
	: ParticleSystem(numParticles)
{
	/* --------- reserve dynamic arrays as we know the needed capacity --------- */
	m_particles.reserve(m_numParticles);
	m_springs.reserve(m_numParticles);
	// reserve double the space for the system state, ...
	// ... since we will be storing positions at even  ...
	// ... and speed at odd indices
	vector<Vector3f> vecstate;
	vecstate.reserve(2 * m_numParticles);

	// fill in code for initializing the state based on the number of particles
	for (int i = 0; i < m_numParticles; i++)
	{
		// for this system, we care about the position and the velocity
		Vector3f particle_pos( (i+1) * m_spring_rest_length, 0.f, 0.f );
		Vector3f particle_speed(0.f, 0.f, 0.f ); // give no initial speed

		m_particles.emplace_back(/*id */i,
			                       /*position*/particle_pos,
														 /*speed*/particle_speed,
													 	 /*system state*/vecstate);
	}
	// update the m_vVecState that is updated by passed reference in emplace_back
	this->setState(vecstate);

	/* ----------------------- add neighbour connections ----------------------- */
	// 0--->1--->2, since a pendulum, connect i to i+1
	for (int i = 0; i < m_numParticles - 1; i++)
	{
		this->connectParticles(&m_particles[i], &m_particles[i+1]);
	}

}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
	// keep the particle information up to date
	for (unsigned int i = 0; i < state.size(); i++)
	{
		if(i % 2 == 0) m_particles[i/2].m_position = state[i];
		else m_particles[(i-1)/2].m_speed = state[i];
	}

	// the derivative state to be populated and returned:
	vector<Vector3f> f;
	// reserve required memory for the derivative state:
	f.reserve( state.size() );

	// this is a second order ODE, and we store both the ...
	// ... particle's position and its velocity in the system, ...
	// ... position - even indices, velocity - odd indices (since start from 0)

	for (unsigned int i = 0; i < state.size(); i++)
	{
		const float particle_mass = 1;

		if (i%2 == 0)
		{ // if even - compute derivative of x, which is v (position'=velocity)
			// hardcoded corners (pins the cloth to left and right corners)
			if ( (i==0) || (i == 420))
				f.push_back(Vector3f(0.f));
			else
				f.push_back(state[i+1] * particle_mass);
		}

		// hardcoded corners (pins the cloth to left and right corners)
		else if ( (i==1) || (i == 421) )
		{
			f.push_back(Vector3f(0.f));
		}

		else // odd index
		{

			// 1. get gravity force
			Vector3f gravity = this->computeGravity(particle_mass);

			// 2. get viscous drag
			Vector3f viscous_drag = this->computeViscousDrag(m_particles[(i-1)/2], particle_mass);
			// 3. get spring force:
			Vector3f spring_force = this->computeSpringForce(m_particles[(i-1)/2], particle_mass);
			// 4. sum all forces
			Vector3f net_force = gravity + spring_force + viscous_drag;
			// 5. get acceleration (second derivative of x, in a system (x, x') )
			// assume all particle masses are equal and are 1.0:
			Vector3f acceleration = net_force;

			f.push_back(acceleration);
		}
	}
	return f;
}

// render the system (ie draw the particles)
void PendulumSystem::draw()
{
	// keep the particle information up to date (since RK4 library does not call the SetState method)
	for (unsigned int i = 0; i < m_vVecState.size(); i++)
	{
		if(i % 2 == 0) m_particles[i/2].m_position = m_vVecState[i];
		else m_particles[(i-1)/2].m_speed = m_vVecState[i];
	}

	for (int i = 0; i < m_numParticles; i++)
	{
		Vector3f pos = m_particles[i].m_position;//  position of particle i. YOUR CODE HERE
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		// glutSolidSphere(0.025f,10.0f,10.0f);
		glutWireSphere(0.01f,10.0f,10.0f);
		glPopMatrix();

		// draw the actual springs (optional)
		for (unsigned int j = 0; j < m_particles[i].m_neighbour_ids.size(); j++)
		{
			Vector3f pos2 = m_particles[m_particles[i].m_neighbour_ids[j]].m_position;
			glPushMatrix();
			glLineWidth(100);
			glBegin(GL_LINES);
			glVertex3f(pos[0], pos[1], pos[2]);
			glVertex3f(pos2[0], pos2[1], pos2[2]);
			glEnd();
			glPopMatrix();
		}
	}
}
