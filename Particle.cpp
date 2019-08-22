/*

REPORT:

This is the Particles file, where I have made a constructor for the particles. The reason I have done this is because it will help me
construct the particles and to put into the particle list during the observation phase. Furthermore, I have made a set X, set Y and
set co ordinate as it will make it easier for me to alter the particle list that way. The building of the constructor made it easier
for me to implement my algorithm as it is a quick and easy set up for the particles. I have also added comments on each of the
methods to explain the use.

Instance variable report is on Particle.h


*/

#include "Particle.h"

// constructor of the co ordinates and the position of the robot
 Particle::Particle(int x, int y, Orientation orientation)
 {
   this->xValue = x;
   this->yValue = y;
   this->oValue = orientation;
 }

// x-co-ordinate of the particle
int Particle::getX()
{
  return xValue;
}

// y-co-ordinate of the particle
int Particle::getY()
{
  return yValue;
}

// Orientation of the particle
Orientation Particle::getOrientation()
{
  return oValue;
}

void Particle::setX(int x)
{
  xValue = x;
}

void Particle::setY(int y)
{
  yValue = y;
}

void Particle::setOrientation(Orientation o){
  oValue = o;
}
