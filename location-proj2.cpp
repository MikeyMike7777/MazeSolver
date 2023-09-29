/**
* file: location-proj2
* author: Michael Mathews
* course: CSI 3334
* assignment: project 2
* due date: February 10, 2022
* version: 11.7
*
* This file creates the Location class for project 2 and
* defines relevant functions
 */

#include "location-proj2.h"
#include <cassert>

/* Default Constructor
*  parameters:
*      none
*  return value: none
*
* This function initializes variables for the location class
*/
Location::Location(){
    this->word = "";
    this->iterationMode = CHANGE_LETTER;
    this->indexToChange = 0;
    this->nextLetter = 'a';
}

/* iterationBegin
*  parameters:
*      none
*  return value: none
*
* This function sets the starting mode, index, and letter of a location
*/
void Location::iterationBegin(){
    this->iterationMode = CHANGE_LETTER;
    this->indexToChange = 0;
    this->nextLetter = 'a';
    //make sure it is a different letter
    if(this->nextLetter == this->word[this->indexToChange]){
        this->nextLetter++;
    }
}

/* iterationCurrent
*  parameters:
*       none
*  return value: the neighbor of the current location
*
* This function gets the neighboring location of a current location based on
* the mode, index, and letter
*/
Location Location::iterationCurrent() const{
    Location neighbor;
    neighbor.word = this->word;
    
    assert(this->iterationMode != DONE);
    
    //find neighbor based on iterationMode
    if(this->iterationMode == CHANGE_LETTER){
        neighbor.word[this->indexToChange] = this->nextLetter;
    }
    else if(this->iterationMode == INSERT_LETTER){
        //add 1 letter to correct spot
        neighbor.word.insert(this->indexToChange, 1, this->nextLetter);
    }
    else if(this->iterationMode == DELETE_LETTER){
        //get rid of 1 letter
        neighbor.word.erase(this->indexToChange,1);
    }

    return neighbor;
}

/* iterationAdvance
 *  parameters:
 *      none
 *  return value: none
 *
 * This function iterates the next letter, index, or mode based on the current
 * iteration of the word
*/
void Location::iterationAdvance(){
    //make sure the location is not done
    assert(this->iterationMode != DONE);
    
    //loop next letter at end of alphabet and increase index or if deleting
    if(this->nextLetter == 'z' or
    (this->nextLetter == 'y' and this->word[this->indexToChange] == 'z') or
    this->iterationMode == DELETE_LETTER){
        this->nextLetter = 'a';
        this->indexToChange++;
        //if passes last index, reset index and go to next mode
        //insert letter goes for one extra index b/c needs to add letter to end
        if(this->iterationMode != INSERT_LETTER and
        this->indexToChange == this->word.length()){
            this->iterationMode++;
            this->indexToChange = 0;
        }
        else if(this->indexToChange == this->word.length()+1) {
            this->iterationMode++;
            this->indexToChange = 0;
        }
    }
    //if not end of alphabet, find next letter
    else{
        this->nextLetter++;
    }
    
    //if it is the same letter as in the word and correct mode, skip it
    if(this->iterationMode == CHANGE_LETTER and
    this->nextLetter == this->word[this->indexToChange]){
        this->nextLetter++;
    }
}

/* iterationDone
*  parameters:
*      none
*  return value: true or false if iterationMode is done or not
*
* This function determines if the iterationMode of the current location is DONE
*/
bool Location::iterationDone() const{
    bool done = false;
    //make done true if that location is done
    if(this->iterationMode == DONE){
        done = true;
    }
    return done;
}

/* operator==
*  parameters:
*      loc - location to be compared with
*  return value: true or false if two words are the same or not
*
* This function determines if two locations are equal to each other
*/
bool Location::operator==(const Location &loc) const{
    bool equal = false;
    //check to see if words are the same
    if(this->word == loc.word){
        equal = true;
    }
    return equal;
}

/* operator<<
*  parameters:
*      os - output stream to write to
*      loc - location to output
*  return value: output stream for a location
*
* This function overloads the extraction operator for the location class
*/
ostream & operator<<(ostream &os, const Location &loc){
    os << loc.word;
    return os;
}

/* operator>>
*  parameters:
*      is - input stream to read from
*      loc - location read in
*  return value: input stream for a location
*
* This function overloads the insertion operator for the location class
*/
istream & operator>>(istream &is, Location &loc){
    is >> loc.word;
    return is;
}

/* operator>>
*  parameters:
*      loc - location to compare with internal location
*  return value: true or false based on size of the internal and the
*  parameter passed location
*
* This function overloads the less than operator for the location class
*/
bool Location::operator<(const Location &loc) const{
    bool lessThan = false;
    if(this->word < loc.word){
        lessThan = true;
    }
    return lessThan;
}
