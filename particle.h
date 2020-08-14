#ifndef PARTICLE_H
#define PARTICLE_H

#include <vecmath.h>
#include <vector>
#include <map>
#include <iostream>
// #include "spring.h"

class Spring; // defined here since used in Particle class

class Particle
{
public:
	/* constructor */
		Particle();
		Particle(unsigned int id);
		Particle(unsigned int id, const Vector3f& position);
		Particle(unsigned int id, const Vector3f& position, const Vector3f& speed);
		Particle(unsigned int id, const Vector3f& position, const Vector3f& speed,
		         std::vector<Vector3f>& system_state);
	/* copy constructor */
		Particle(const Particle& other) {std::cout << "Copied Particle\n"; }

	/* public methods */
		void addNeighbour(unsigned int id);
		void print(bool log);
		void print();

	/* public member variables */
		unsigned int m_id;
		Vector3f m_position;
		Vector3f m_speed;

		std::vector<unsigned int> m_neighbour_ids;
		std::vector<unsigned long  int> m_attached_spring_ids;
	/* NOTE : the above are made public because they will be accessed by Spring */
};

#endif
