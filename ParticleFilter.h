/*

REPORT:

In my ParticleFilter.h file, I made a bunch of variables which helped me for the methods in ParticleFilter.cpp
Variables such as x_offset, y_offset help me determine the offset of the robot
robotOrientation and orientation help me find out the current orientation of the observation
rows and cols to help me identify the amount of times the for loop should be iterated
and the maze which helped me identfy the position within the maze for comparison with the observation

*/

#ifndef COSC_ASS_ONE_PARTICLE_FILTER
#define COSC_ASS_ONE_PARTICLE_FILTER

#include "Particle.h"
#include "ParticleList.h"
#include "Types.h"

#define MAZE_SIZE          100

class ParticleFilter {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Initialise a new particle filter with a given maze of size (x,y)
   ParticleFilter(Grid maze, int rows, int cols);

   // Clean-up the Particle Filter
   ~ParticleFilter();

   // A new observation of the robot, of size 3x3
   void newObservation(Grid observation);

   // Return a DEEP COPY of the ParticleList of all particles representing
   //    the current possible locations of the robot
   ParticleList* getParticles();

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

 private:
  // Variables
  char** x_maze;
  int x_rows;
  int x_cols;
  ParticleList* p_list = new ParticleList();
  Orientation orientation;
  Orientation robotOrientation;
  int x_offset = 0;
  int y_offset = 0;

};

#endif // COSC_ASS_ONE_PARTICLE_FILTER
