#ifndef SPRING_H
#define SPRING_H

#include "particle.h"

class Spring
{
public:
	/* static non-instance methods */
		static unsigned long int generateSpringID(unsigned int id1, unsigned int id2);

	/* constructor */
		Spring(Particle* p1, Particle* p2);
		Spring(Particle* p1, Particle* p2, float rest_len);
		Spring(Particle* p1, Particle* p2, float rest_len, float stiffness);
	/* copy constructor */
		Spring(const Spring& other) {std::cout << "Copied Spring\n"; }

	/* public methods */
		void visualise();

	/* public member variables */
		unsigned long int m_id; // two particle ids concatenated as ints
		float m_rest_length;
		float m_stiffness;
	// have pointers to both connected particles:
		Particle* m_particle1;
		Particle* m_particle2;
};

#endif
