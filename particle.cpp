
#include <vecmath.h>
#include <vector>
#include <iostream>

#include "particle.h"

/* -------------------------------- Particle -------------------------------- */

Particle::Particle()
  : m_id(0), \
    // m_position(ParticleSystem::m_root_particle_offset),
    m_position(Vector3f(0.0, 0.0, 0.0)), \
    m_speed(Vector3f(0.0, 0.0, 0.0)) \
  {}

Particle::Particle(unsigned int id)
  : m_id(id), \
    // m_position(ParticleSystem::m_root_particle_offset),
    m_position(Vector3f(0.0, 0.0, 0.0)), \
    m_speed(Vector3f(0.0, 0.0, 0.0)) \
  {}

Particle::Particle(unsigned int id, const Vector3f& position)
  : m_id(id), \
    // m_position(ParticleSystem::m_root_particle_offset + position),
    m_position(Vector3f(0.0, 0.0, 0.0) + position), \
    m_speed(Vector3f(0.0, 0.0, 0.0)) \
  {}

Particle::Particle(unsigned int id, const Vector3f& position,const Vector3f& speed)
  : m_id(id), \
    // m_position(ParticleSystem::m_root_particle_offset + position),
    m_position(Vector3f(0.0, 0.0, 0.0) + position), \
    m_speed(speed) \
  {}



Particle::Particle(unsigned int id, const Vector3f& position,
                   const Vector3f& speed, std::vector<Vector3f>& system_state)
  : m_id(id), \
    // m_position(ParticleSystem::m_root_particle_offset + position),
    m_position(Vector3f(0.0, 0.0, 0.0) + position), \
    m_speed(speed) \
  {
    // update the m_vVecState by passed reference:
    system_state.emplace_back(m_position);
    system_state.emplace_back(m_speed);
  }

void Particle::print(bool log)
{
  std::cout << "@m_id = " << m_id << ", ";
  std::cout << " m_position = " << m_position.getprint() << ", ";
  std::cout << " m_speed = " << m_speed.getprint() << ", " << std::endl;

  std::cout << "Neighbours: " << m_neighbour_ids.size() << std::endl;

  for (int i : m_neighbour_ids)
  {
    std::cout << i << ", ";
  }
  std::cout << "\nSprings: " << m_attached_spring_ids.size() << std::endl;
  for (int i : m_attached_spring_ids)
  {
    std::cout << i << ", ";
  }

  std::cout << std::endl << std::endl;
}

void Particle::print() {}
