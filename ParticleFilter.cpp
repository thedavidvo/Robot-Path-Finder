/*

REPORT:

The ParticleFilter.cpp file was the most challenging file to work with. While the ParticleFilter and the getParticles method
were quite do-able, although the pseudocode was given to us,  I had to think about the implementation for the newObservation method

PSEUDOCODE:

First iteration is different to all the future iterations...
IF the particle list is empty
  find all the possible '.' in the map, and put them on a temporary list.
  compare all those '.' to the first observation and add it to the particle list
  repeat until complete

ELSE
  the robot can either move or rotate
      IF the robot has rotated
          change each of the orientation in the current particle list as nothing will be eliminated
          end of observation
      ELSE the robot has moved
          find the offset of the robot - find which way it has moved
          make a new set of particles and offset the X and Y value
          compare to observation, if matched - add it to the list.
END

For some reason, my final positions are double printing - which is leading me to fail the test. Furthermore, I am unable to clear
the particle list which will lead for me to end up with a malloc error. However, after hard thinking, I had finally
figured it out. Nevertheless, I managed to get the final positions to be correct with the .pos files.

*/

#include "ParticleFilter.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

// Initialise a new particle filter with a given maze of size (x,y)
ParticleFilter::ParticleFilter(char** maze, int rows, int cols)
{
  this->x_maze = maze;
  this->x_rows = rows;
  this->x_cols = cols;
}

// Clean-up the Particle Filter
ParticleFilter::~ParticleFilter()
{
  //UNUSED CODE
}

// A new observation of the robot, of size 3x3
void ParticleFilter::newObservation(Grid observation)
{
  ParticleList* temp_list = new ParticleList();

  //repopulate the temp_list from the p_list
  for(int i = 0; i < p_list -> getNumberParticles(); i++)
  {
    ParticlePtr p = new Particle(p_list -> get(i) -> getX(), p_list -> get(i) -> getY(), robotOrientation);
    temp_list -> add_back(p);
  }

  //identifies the current orientation of the robot
  if(observation[1][1] == '^') {
    orientation = ORIEN_UP;
  } else if(observation[1][1] == '>') {
    orientation = ORIEN_RIGHT;
  } else if(observation[1][1] == 'v') {
    orientation = ORIEN_DOWN;
  } else {
    orientation = ORIEN_LEFT;
  }

  // FIRST ITERATION ONLY, AS THE FIRST ITERATION IS DIFFERENT TO THE OTHER ITERATIONS
  if(p_list->getNumberParticles() == 0)
  {
    //lets the robotOrientation = orientation for constructor set-up
    robotOrientation = orientation;

    //finds all the '.' in the maze and creates a particle for comparison
    for(int j = 0; j < x_rows; j++)
    {
      for(int i = 0; i < x_cols; i++)
      {
        if(x_maze[j][i] == '.')
        {
          ParticlePtr p = new Particle(i,j,robotOrientation);
          temp_list -> add_back(p);
        }
      }
    }

    for(int i = 0; i < temp_list -> getNumberParticles(); i++)
    {
      //Gets the particle's x and y point and compares to the maze... to see if it matches with observation.
      //If it matches, it adds those points into the P
      if(
        x_maze[temp_list -> get(i) -> getY()-1][temp_list -> get(i) -> getX()] == observation[0][1] &&
        x_maze[temp_list -> get(i) -> getY()-1][temp_list -> get(i) -> getX()+1] == observation[0][2] &&
        x_maze[temp_list -> get(i) -> getY()][temp_list -> get(i) -> getX()+1] == observation[1][2] &&
        x_maze[temp_list -> get(i) -> getY()+1][temp_list -> get(i) -> getX()+1] == observation[2][2] &&
        x_maze[temp_list -> get(i) -> getY()+1][temp_list -> get(i) -> getX()] == observation[2][1] &&
        x_maze[temp_list -> get(i) -> getY()+1][temp_list -> get(i) -> getX()-1] == observation[2][0] &&
        x_maze[temp_list -> get(i) -> getY()][temp_list -> get(i) -> getX()-1] == observation[1][0] &&
        x_maze[temp_list -> get(i) -> getY()-1][temp_list -> get(i) -> getX()-1] == observation[0][0])
        {
          ParticlePtr p = new Particle(temp_list -> get(i) -> getX(), temp_list -> get(i) -> getY(), robotOrientation);
          p_list -> add_back(p);
        }
      }
      //clears the temp_list for the next sets of iteration
      temp_list -> clear();
    }
    else
    {
      //check to see if the orientation has changed
      if(robotOrientation != orientation)
      {
        robotOrientation = orientation;

        //fixes the existing values in the particle list
        for(int i = 0; i < p_list -> getNumberParticles(); i++)
        {
          p_list -> get(i) -> setOrientation(robotOrientation);
        }

        //clears the temp_list for the next set of iterations
        temp_list -> clear();
      }
      else
      {

        if(p_list != 0)
        p_list -> clear();
        p_list = new ParticleList();

        //finding the offset values
        if(orientation == ORIEN_UP) {
          y_offset--;
        } else if(orientation == ORIEN_RIGHT) {
          x_offset++;
        } else if(orientation == ORIEN_DOWN) {
          y_offset++;
        } else {
          x_offset--;
        }

        //iterates through the array and changes the offset coordinates
        for(int i = 0; i < temp_list -> getNumberParticles(); i++)
        {
          //offset the current coordinate and compares it to the offsetted coordinate
          ParticlePtr a = new Particle(temp_list -> get(i) -> getX() + x_offset, temp_list -> get(i) -> getY() + y_offset, temp_list -> get(i) -> getOrientation());

          //checking of the offsetted positions if it matches with observation added back
          if(x_maze[a->getY()-1][a->getX()] == observation[0][1] &&
          x_maze[a->getY()-1][a->getX()+1] == observation[0][2] &&
          x_maze[a->getY()][a->getX()+1] == observation[1][2] &&
          x_maze[a->getY()+1][a->getX()+1] == observation[2][2] &&
          x_maze[a->getY()+1][a->getX()] == observation[2][1] &&
          x_maze[a->getY()+1][a->getX()-1] == observation[2][0] &&
          x_maze[a->getY()][a->getX()-1] == observation[1][0] &&
          x_maze[a->getY()-1][a->getX()-1] == observation[0][0])
          {
            p_list -> add_back(a);
          }
        }

        //resetting the offset values
        x_offset = 0;
        y_offset = 0;

        //clearing the temp list for the next set of iterations
        temp_list -> clear();
      }
    }
    //END OF EVERY OTHER ITERATION THAN FIRST ITERATION
  }

// Return a DEEP COPY of the ParticleList of all particles representing
//    the current possible locations of the robot
ParticleList* ParticleFilter::getParticles()
{
    ParticleList* deepCopy = new ParticleList();

    for(int i = 0; i < p_list -> getNumberParticles(); i++)
    {
      ParticlePtr p = new Particle(p_list -> get(i) -> getX(), p_list -> get(i) -> getY(), p_list -> get(i) -> getOrientation());
      p -> setX(p_list -> get(i) -> getX());
      p -> setY(p_list -> get(i) -> getY());
      p -> setOrientation(p_list -> get(i) -> getOrientation());
      deepCopy -> add_back(p);
    }

    return deepCopy;
  }
