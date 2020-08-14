#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H

#include <vecmath.h>
#include <vector>

#include "particleSystem.h"
#include "pendulumSystem.h"

class ClothSystem: public PendulumSystem
{
///ADD MORE FUNCTION AND FIELDS HERE
public:
	ClothSystem(int numParticles);
	// use the parent classes (PendulumSystem) evalF method:
	// vector<Vector3f> evalF(vector<Vector3f> state);
	// use the parent classes (PendulumSystem) draw method:
	// void draw();
	void setupStructuralSprings();
	void setupShearSprings();
	void setupFlexSprings();

private:
	void addShearNeighbours(Particle* p);
	void addFlexNeighbours(Particle* p);

};


#endif
