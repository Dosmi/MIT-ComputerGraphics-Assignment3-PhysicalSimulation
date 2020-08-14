#include "ClothSystem.h"
#include <math.h>       /* sqrt */
//TODO: Initialize here
// const Vector3f ParticleSystem::m_root_particle_offset = Vector3f(.3f, 0.f, 0.f);

ClothSystem::ClothSystem(int numParticles)
	//: PendulumSystem(numParticles)
{
	m_numParticles = numParticles * numParticles;

	/* --------- reserve dynamic arrays as we know the needed capacity --------- */
	m_particles.reserve(m_numParticles);
	m_springs.reserve(m_numParticles);
	// reserve double the space for the system state, ...
	// ... since we will be storing positions at even  ...
	// ... and speed at odd indices
	vector<Vector3f> vecstate;
	vecstate.reserve(2 * m_numParticles);

	// fill in code for initializing the state based on the number of particles
	unsigned int particle_id = 0;
	for (int i = 0; i < numParticles ; i++)
	{
		for (int j = 0; j < numParticles; j++)
		{
			// float offset = 0.665;
			float offset = 1; // start at rest length
			// for this system, we care about the position and the velocity
			Vector3f particle_pos( /* x */offset * (i+1) * m_spring_rest_length,
			                       /* y */0.f,
			                       /* z */offset * (j+1) * m_spring_rest_length);
			Vector3f particle_speed(0.f, 0.f, 0.f ); // give no initial speed

			m_particles.emplace_back(/*id */particle_id,
														   /*position*/particle_pos,
															 /*speed*/particle_speed,
															 /*system state*/vecstate);
			particle_id++;
		}
	}

	// set the particle system state to the one ...
	// ... that is updated when adding new particle
	this->setState(vecstate);

	/* ----------------------- add neighbour connections ----------------------- */
	this->setupStructuralSprings();
	this->setupShearSprings();
	this->setupFlexSprings();
}


void ClothSystem::setupStructuralSprings()
{
	// since the cloth is square, ...
	// ... get length of square side as sqrt of nr of all particles
	unsigned int side_len = sqrt(m_numParticles);
	for (unsigned int i = 0; i < m_numParticles - 1; i++)
	{
		// check if current particle is not in the last column, ...
		// ... if not in last column, make connection with the next column same row.
		if (i+side_len <= m_numParticles-1)
			this->connectParticles(&m_particles[i], &m_particles[i+side_len]);
		// check if current particle is not in the last row, ...
		// ... if not in last row, make connection with following (+1) particle
		if((i+1) % side_len != 0)
			this->connectParticles(&m_particles[i], &m_particles[i+1]);
	}
}

void ClothSystem::setupShearSprings()
{
	// since the cloth is square, ...
	// ... get length of square side as sqrt of nr of all particles
	unsigned int side_len = sqrt(m_numParticles);
	// adjust the shear spring unique features so that its:
	// ... rest length is twice as long and stiffeness 100 times smaller ...
	// ... than for the default structural springs.
	float shear_spring_rest = m_spring_rest_length * 2;
	float shear_spring_stiffness = m_spring_stiffness / 100;

	for (unsigned int i = 0; i < m_numParticles - side_len; i++)
	{
		if(i % side_len == 0) // if first row particle:
		{ // ... connect with next column down one row particle:
			this->connectParticles(&m_particles[i], &m_particles[i+side_len+1],
			                       shear_spring_rest, shear_spring_stiffness);
		}

		else if((i+1) % side_len == 0) // if last row particle:
		{ // ... connect with next column up one row particle:
			this->connectParticles(&m_particles[i], &m_particles[i+side_len-1],
			                       shear_spring_rest, shear_spring_stiffness);
		}

		else
		{ // connect with next column both up and down one row particles:
			this->connectParticles(&m_particles[i], &m_particles[i+side_len+1],
			                       shear_spring_rest, shear_spring_stiffness);
			this->connectParticles(&m_particles[i], &m_particles[i+side_len-1],
			                       shear_spring_rest, shear_spring_stiffness);
		}
	}
}

void ClothSystem::setupFlexSprings()
{
	// since the cloth is square, ...
	// ... get length of square side as sqrt of nr of all particles
	unsigned int side_len = sqrt(m_numParticles);
	// adjust the flexion spring unique features so that its:
	// ... rest length is twice as long and stiffeness 100 times smaller ...
	// ... than for the default structural springs.
	float flex_spring_rest = m_spring_rest_length * 2;
	float flex_spring_stiffness = m_spring_stiffness / 100;

	for (unsigned int i = 0; i < m_numParticles - 1; i++)
	{ // there are three cases:
		// (NOTE: in this case n is hardcoded as 2)
		// 1. Add two neighbours - n away to the right and n away down ...
		// ... if there exists a particle n rows down and n columns right, connect both
		if ( ((i % side_len) + 2 < side_len) && (i + 2*side_len <= m_numParticles-1) )
		{ // connect with +n to the right side:
			this->connectParticles(&m_particles[i], &m_particles[i + 2*side_len],
			                       flex_spring_rest, flex_spring_stiffness);
			// connect with +n down particle:
			this->connectParticles(&m_particles[i], &m_particles[i + 2],
			                       flex_spring_rest, flex_spring_stiffness);
		}
		// if right neighbour condition failed, add down:
		else if ( (i % side_len) + 2 < side_len)
		{
			this->connectParticles(&m_particles[i], &m_particles[i + 2],
														 flex_spring_rest, flex_spring_stiffness);
		}
		else if (i + 2*side_len <= m_numParticles-1)
		{
			this->connectParticles(&m_particles[i], &m_particles[i + 2*side_len],
														 flex_spring_rest, flex_spring_stiffness);
		}
		// and if none - then don't add any edges.
	}
}

// ClothSystem inherits evalF and draw from PendulumSystem
// ... if needed later, overwrite here 
// TODO: implement evalF
// for a given state, evaluate f(X,t)
// vector<Vector3f> ClothSystem::evalF(vector<Vector3f> state)
// {
// 	return vector<Vector3f>();
// }

///TODO: render the system (ie draw the particles)
// void ClothSystem::draw()
// {
// }
