#include <vecmath.h>
#include <iostream>
#include "particleSystem.h"
#include "spring.h"

/* --------------------------------- Spring --------------------------------- */
unsigned long int Spring::generateSpringID(unsigned int id1, unsigned int id2)
{
  // order numbers so that id1 > id2:
  unsigned int higher_val = id1 > id2 ? id1 : id2;
  unsigned int lower_val = id1 < id2 ? id1 : id2;

  unsigned int decimal_shift = 10;
  while (decimal_shift <= lower_val) decimal_shift *= 10;

  return higher_val * decimal_shift + lower_val;
}

// spring constructor
Spring::Spring(Particle* p1, Particle* p2)
  :	m_rest_length(ParticleSystem::m_spring_rest_length), \
    m_stiffness(ParticleSystem::m_spring_stiffness), \
    m_particle1(p1), \
    m_particle2(p2)
  {
    // generate the id from the two particle ids given:
    m_id = Spring::generateSpringID(p1->m_id, p2->m_id);
  }

Spring::Spring(Particle* p1, Particle* p2, float rest_len, float stiffness)
:	m_rest_length(rest_len), \
  m_stiffness(stiffness), \
  m_particle1(p1), \
  m_particle2(p2)
{
  // generate the id from the two particle ids given:
  m_id = Spring::generateSpringID(p1->m_id, p2->m_id);
}


void Spring::visualise()
{
  std::cout << "(" << m_particle1->m_id << ")"
            << " ----- " << m_id << " ----- "
            << "(" << m_particle2->m_id << ")" << std::endl;
  std::cout << "rest len:" << m_rest_length << std::endl;
  std::cout << "stiffness:" << m_stiffness << std::endl;

}
