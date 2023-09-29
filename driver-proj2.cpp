/**
* file: driver-proj2
* author: Michael Mathews
* course: CSI 3334
* assignment: project 2
* due date: February 10, 2022
* version: 11.7
*
* This file find the shortest path from one word to another in a word melt
*/

#include <iostream>
#include <map>
#include "maze-proj2.h"
#include "location-proj2.h"
#include "arrayqueue-student-proj2.h"

/* main
*  parameters:
*      argc -- the number of arguments from the command line
*      argv -- the command line argument values
*  return value: 0 (indicating a successful run)
*
* This function uses locations from the user to create and solve a maze
* from a given starting point to a given ending point if possible
*/
int main(int argc, const char * argv[]) {
    ArrayQueue<Location> q;
    map<Location, Location> myMap;
    Maze m;
    Location current, next, end;
    bool found = false, done = false;
    
    cin >> m;
    
    //set first item in queue
    q.add(m.getStartLocation());
    //set first map location
    myMap[m.getStartLocation()] = m.getStartLocation();
    
    //if only one item
    if(m.isEndLocation(m.getStartLocation())){
        found = true;
        end = m.getStartLocation();
    }
    
    //while the queue is not empty and the ending location has not been found
    //fill the queue and sequentially the map
    while(q.getLength() > 0 and !found){
        //pull one location off queue
        current = q.getFront();
        current.iterationBegin();
        q.remove();
        //look at all valid neighbor locations and place on queue
        while(!current.iterationDone()){
            next = current.iterationCurrent();
            //if it is a valid location add it to queue
            if(m.isValidLocation(next)){
                //if it is not on map, add it to map with new neighbor as key
                if(myMap.find(next) == myMap.end()){
                    q.add(next);
                    myMap.insert(pair<Location, Location>(next, current));
                }
                //set found to true if end is found
                if(m.isEndLocation(next)){
                    found = true;
                    end = next;
                }
            }
            current.iterationAdvance();
        }
    }
    
    Location flip[myMap.size()];
    int i = 0;
    
    if(found){
        cout << "Solution found" << endl;
        while(!done){
            flip[i] = end;
            if(myMap[end] == end){
                done = true;
            }
            else{
                end = myMap[end];
                i++;
            }
        }
        while(i >= 0){
            cout << flip[i] << endl;
            i--;
        }
    }
    else {
        cout << "No solution" << endl;
    }
    return 0;
}
