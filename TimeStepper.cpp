#include "TimeStepper.hpp"
#include <iostream>
///COMPLETED: implement Explicit Euler time integrator here
void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{ /* parameters use lowerCamelCase, local variables use underscore_casing */
  // 'Euler method' is the simplest time integrator.
  /*
   * given ANY particle system, and the step size (h)
   *       compute a new state as follows:
   *               X(t+h) = X + h * derivative_X(t)
   *              (new_state = given_state + stepSize * state_derivative)
   */
  // iterating through all particles, we will gather a new state:
  vector<Vector3f> new_state;
  // to be updated is the state of the passed PS (particle system)
  vector<Vector3f> given_state = particleSystem->getState();
  // for each particle in the system, ...
  // 'evalF' will compute their states derivatives
  vector<Vector3f> state_derivative = particleSystem->evalF(given_state);

  // for every particle in the system, compute particle new state using
  // ... Euler's method:
  for (unsigned int i = 0; i < given_state.size(); i++)
  {
    Vector3f new_particle_state;
    new_particle_state = given_state[i] + stepSize * state_derivative[i];

    new_state.push_back(new_particle_state);
  }
  // update the state after all particles have been updated:
  particleSystem->setState(new_state);
}
///COMPLETED: implement Trapzoidal rule here
void Trapzoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{/* parameters use lowerCamelCase, local variables use underscore_casing */
  // 'Trapzoidal method' is a little bit more advanced time integrator.
  /*
   * given ANY particle system, and the step size (h)
   *       compute a new state as follows:
   *              compute derivative zero [derivative_X(t)]:
   *               f0 = f(X,t) (derivative at point X)
   *              compute derivative one [derivative_X(t+h)]:
   *               f1 = f(X+h*f0,t+h) (derivative at X nudged by h at slope f0)
   *               X(t+h) = X + h/2 * (f0 + f1)/2
   *              (new_state = given_state + stepSize/2 * (f0 + f1)/2 )
   */
   // to be updated is the state of the passed PS (particle system)
   vector<Vector3f> original_state = particleSystem->getState();
   vector<Vector3f> intermediate_state;
   // iterating through all particles, we will compute the new state:
   vector<Vector3f> new_state;
   // compute intermediate derivative (slope, which is used ...
   // ... to take the initial step)
   vector<Vector3f> f0 = particleSystem->evalF(original_state);

   // for every particle in the system, compute particle intermediate state
   // ... using f0 slope:
   for (unsigned int i = 0; i < original_state.size(); i++)
   {
     Vector3f intermediate_particle_state;
     // take an euler step (step from original state with first slope f0)
     intermediate_particle_state = original_state[i] + stepSize * f0[i];
     intermediate_state.push_back(intermediate_particle_state);
   }
   // compute another derivative at that new state that got updated after...
   // ... moving by using the initial slope:
   vector<Vector3f> f1 = particleSystem->evalF(intermediate_state);

   for (unsigned int i = 0; i < original_state.size(); i++)
   {
     Vector3f new_particle_state;
     // average the two slopes to get a more reliable new slope:
     Vector3f derivative_average = (f0[i] + f1[i]) / 2.0;
     // finally, for each particle i will compute the new trapizoidal state
     new_particle_state = original_state[i] + stepSize * derivative_average;

     new_state.push_back(new_particle_state);
   }
   // ONLY AFTER we have the final state do we update the particle state:
   particleSystem->setState(new_state);
}
