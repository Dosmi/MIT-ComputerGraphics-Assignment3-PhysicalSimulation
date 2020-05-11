#ifndef PENDULUMSYSTEM_H
#define PENDULUMSYSTEM_H

#include <vecmath.h>
#include <vector>
#ifdef _WIN32
#include "GL/freeglut.h"
#else
#include <GL/glut.h>
#endif

#include "particleSystem.h"
#include <iostream>

class ParticleConnection
{
public:
	ParticleConnection(int id, std::vector<int> springs, std::vector<int> neighbours)
		: m_id(id), m_attached_springs(springs), m_neighbours(neighbours) {}
	ParticleConnection(int id)
		: m_id(id)
	{
		m_attached_springs.push_back(-1);
		m_neighbours.push_back(-1);
	}
	int m_id;
	std::vector<int> m_attached_springs;
	std::vector<int> m_neighbours;

	// further methods:
	void addNeighbour(int neighbourId)
	{
		if ( (m_neighbours.size() == 1) && (m_neighbours[0] == -1) )
		{
			m_neighbours.erase ( m_neighbours.begin() );
			m_neighbours.push_back(neighbourId);
		}
		else { m_neighbours.push_back(neighbourId); }
	}

	void addSpring(int springId)
	{
		if ( (m_attached_springs.size() == 1) && (m_attached_springs[0] == -1) )
		{
			m_attached_springs.erase ( m_attached_springs.begin() );
			m_attached_springs.push_back(springId);
		}
		else { m_attached_springs.push_back(springId); }
	}

	int getIdInState()
	{

	}

	void Print()
	{
		std::cout << "Particle (" << m_id << ")" << std::endl;
		std::cout << "its neighbours:" << std::endl;
		for (unsigned int i = 0; i < m_neighbours.size(); i++)
		{
			std::cout << m_neighbours[i] << " ";
		}
		std::cout << std::endl;
		std::cout << "springs attached:" << std::endl;
		for (unsigned int i = 0; i < m_attached_springs.size(); i++)
		{
			std::cout << m_attached_springs[i] << " ";
		}
		std::cout << std::endl;
	}

};

class Spring
{
public:
	// constructor
	Spring(int id1, int id2, int id3, float len, float stiff)
		: m_particle1(id1),
		  m_particle2(id2),
			m_springId(id3),
			m_rest_length(len),
			m_stiffness(stiff) {}
	void Print()
	{
		std::cout << "(" << m_particle1 << ")---id-" << m_springId << "-ln-"
              << m_rest_length << "---("
						  << m_particle2 << ")" << std::endl;
	}
	// member variables
	int m_particle1;
	int m_particle2;
	int m_springId;
	float m_rest_length;
	float m_stiffness;
};

class PendulumSystem: public ParticleSystem
{
public:
	PendulumSystem(int numParticles);
	vector<Spring> m_springs;
	vector<ParticleConnection> m_particle_connections;

	vector<Vector3f> evalF(vector<Vector3f> state);

	void draw();

};

#endif
