/*

REPORT:

I did not make many modifications of this page but rather just made a couple of instance variables which made it easier to reference
the x y and the orientation of the robot. Furthermore, since I made new methods I had to create the prototype of each method
including the constructor within the Particle.h file.

*/

#ifndef COSC_ASS_ONE_PARTICLE
#define COSC_ASS_ONE_PARTICLE

#include "Types.h"

class Particle {
public:

  /*                                           */
  /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
  /*                                           */

  // x-co-ordinate of the particle
  int getX();

  // y-co-ordinate of the particle
  int getY();

  // Orientation of the particle
  Orientation getOrientation();

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */

  // constructor of the particle for later use
  Particle(int x, int y, Orientation Orientation);
  void setX(int x);
  void setY(int y);
  void setOrientation(Orientation o);

  //private instance variables
private:
  int xValue;
  int yValue;
  Orientation oValue;
};


/*                                           */
/* DO NOT MOFIFY THIS TYPEDEF                */
/*                                           */

// Pointer to a Particle (robot)
typedef Particle* ParticlePtr;

#endif // COSC_ASS_ONE_PARTICLE
