#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <map>
#include <vecmath.h>
#include <vector>
#include <iostream>
#include "particle.h"
#include "spring.h"

using namespace std;

// Particle System abstract class.
class ParticleSystem
{
public:
	/* constructor, getter, setterm, member variables */
		ParticleSystem();
		ParticleSystem(int numParticles);

	/* getter method for the system's state */
		std::vector<Vector3f> getState(){ return m_vVecState; };
	/* setter method for the system's state */
		void setState(const std::vector<Vector3f>  & newState)
		{
			m_vVecState = newState;
			// keep the particle list up to date from the newly computed state:
			for (unsigned int i = 0; i < m_vVecState.size(); i++)
			{
				if(i % 2 == 0) m_particles[i/2].m_position = m_vVecState[i];
				else m_particles[(i-1)/2].m_speed = m_vVecState[i];
			}
		};

	/* functions for particle and spring relationship */
		void connectParticles(Particle* p1, Particle* p2);
		// connect particles with a non-default spring:
		void connectParticles(Particle* p1, Particle* p2, float rest_len, float stiffness);
		void connectParticles(unsigned int p1_id, unsigned int p2_id);

	/* functions computing forces */
		Vector3f computeGravity();
		Vector3f computeGravity(float particle_mass);
		Vector3f computeViscousDrag(Particle& p, float particle_mass);
		Vector3f computeSpringForce(Particle& p, float particle_mass);


	// for a given state, evaluate derivative f(X,t)
	/* (... pure virtual function, implementations in subclasses ... ) */
	virtual std::vector<Vector3f> evalF(std::vector<Vector3f> state) = 0;
	/* (... pure virtual function, implementations in subclasses ... ) */
	virtual void draw() = 0;

/* ------------------------ public member variables ------------------------- */
	int m_numParticles;

	// std::vector<Vector3f> test; (variable test for RK4)
	std::vector<Vector3f> m_vVecState;
	std::vector<Particle> m_particles;
	std::vector<Spring> m_springs;
	std::map <unsigned long int, Spring> m_id_to_spring;

	/* ------------------------ constants for a system ------------------------- */
	static constexpr float m_spring_rest_length =0.1f;
	static constexpr float m_spring_stiffness =12.f;
	static const Vector3f m_root_particle_offset;


};

#endif
