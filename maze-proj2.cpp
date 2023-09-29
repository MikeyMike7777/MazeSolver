/**
* file: maze-proj1
* author: Michael Mathews
* course: CSI 3334
* assignment: project 2
* due date: February 10, 2022
* version: 11.7
*
* This file creates the Maze class for project 2 and
* defines relevant functions
 */

#include "maze-proj2.h"

/* Default constructor
*  parameters:
*      none
*  return value: none
*
* This function is the default constructor for the Maze class
*/

Maze::Maze(void){}

/* getStartLocation
*  parameters:
*      none
*  return value: starting location stored by a Maze
*
* This function gets the nextNode from a LocationStackNode
*/
Location Maze::getStartLocation(void) const{
    return this->startLocation;
}

/* isValidLocation
*  parameters:
*      loc - location to inspect
*  return value: indicates if the location is a valid
*
* This function compares a location to the list of valid locations to see if
* it is a valid location
*/
bool Maze::isValidLocation(const Location &loc) const{
    bool valid = true;
    if(validLocations.find(loc) == validLocations.end()){
        valid = false;
    }
    return valid;
}

/* isEndLocation
*  parameters:
*      loc - location to inspect
*  return value: indicates if the location is the end location
*
* This function compares a location to the end location to see if it is the
* end location
*/
bool Maze::isEndLocation(const Location &loc) const{
    bool isEnd = false;
    if(loc == this->endLocation){
        isEnd = true;
    }
    return isEnd;
}

/* operator>>
*  parameters:
*      is - input stream to read from
*      m - Maze read in
*  return value: input stream for a maze
*
* This function overloads the insertion operator for the Maze class
*/
istream &operator>>(istream &is, Maze &m){
    int lines;
    Location wrd;
    is >> lines;
    m.validLocations.clear();
    if(lines <= 20000 and lines >= 1){
        m.validLocations.begin();
        for(int i = 0; i < lines; i++){
            is >> wrd;
            m.validLocations.insert(wrd);
        }
        is >> m.startLocation;
        is >> m.endLocation;
    }
    return is;
}
