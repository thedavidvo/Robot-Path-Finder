/*

REPORT:

The particle list class was straight forward in terms of implementing the code. I realised that we were not allowed to use
break statements, so I immediately made the fix to that. The particle list class had already come with variables for us to use,
which made the process easier when referring and adding / removing particles from the particle list. While I implemented code for
most of the methods, I did not implement anything for the deconstructor. 

*/

#include "ParticleList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

#define PARTICLE_SIZE      10000
#define LENGTH             100

#ifndef DEBUG
#define DEBUG        0
#endif

// Initialise a new particle filter with a given maze of size (x,y)
ParticleList::ParticleList()
{
  for(int i = 0; i < LENGTH; i++)
  {
    particles[i] = NULL;
  }

  numParticles = 0;
}

// Clean-up the particle list
ParticleList::~ParticleList()
{
  //UNUSED CODE
}

// Number of particles in the ParticleList
int ParticleList::getNumberParticles()
{
  return numParticles;
}

// Get a pointer to the i-th particle in the list
ParticlePtr ParticleList::get(int i)
{
  return particles[i];
}

// Add a particle (as a pointer) to the list
// This class now has control over the pointer
// And should delete the pointer if the particle is removed from the list
void ParticleList::add_back(ParticlePtr particle)
{
  particles[numParticles] = particle;
  numParticles++;

}

// Remove all particles from the list
void ParticleList::clear()
{
  for(int i = 0; i < LENGTH; i++)
  {
    delete particles[i];
  }

  numParticles = 0;
}
