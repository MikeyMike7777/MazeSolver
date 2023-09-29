/**
* file: arrayqueue-student-proj2.h
* author: Michael Mathews
* course: CSI 3334
* assignment: project 2
* due date: February 10, 2022
* version: 11.7
*
* This file implements the arrayqueue class for project 2 and
* contains relevant functions
 */

#ifndef ARRAY_QUEUE_STUDENT_PROJ2_H
#define ARRAY_QUEUE_STUDENT_PROJ2_H

#include "arrayqueue-prof-proj2.h"
#include <cassert>

/* Default Constructor
*  parameters:
*      none
*  return value: none
*
* This function is the default Constructor for the ArrayQueue class
*/
template <class Base>
ArrayQueue<Base>::ArrayQueue(){
    this->length = 0;
    this->capacity = 5;
    this->front = 0;
    this->data = new Base[this->capacity];
}

/* Copy Constructor
*  parameters:
*      q - ArrayQueue to be copied
*  return value: none
*
* This function is the Copy Constructor for the ArrayQueue class
*/
template <class Base>
ArrayQueue<Base>::ArrayQueue(const ArrayQueue<Base> &q){
    //deep copy data members
    this->length = q.length;
    this->capacity = q.capacity;
    this->front = q.front;
    this->data = new Base[this->length];
    for(int i = 0; i < q.length; i++){
        this->data[(this->front + i) % this->capacity] =
        q.data[(this->front + i) % this->capacity];
    }
}

/* Destructor
*  parameters:
*      none
*  return value: none
*
* This function deallocates an ArrayQueue
*/
template <class Base>
ArrayQueue<Base>::~ArrayQueue(){
    delete [] this->data;
}

/* add
*  parameters:
*      item - data to be added to ArrayQueue
*  return value: none
*
* This function adds a value to an ArrayQueue
*/
template <class Base>
void ArrayQueue<Base>::add(const Base &item){
    if(this->length >= this->capacity){
        this->doubleCapacity();
    }
    this->data[(this->front+this->length) % this->capacity] = item;
    this->length++;
}

/* remove
*  parameters:
*      none
*  return value: none
*
* This function removes a value from an ArrayQueue
*/
template <class Base>
void ArrayQueue<Base>::remove(){
    //make sure there is something to remove
    assert(this->length > 0);
    assert(this->front < this->capacity);
    //remove front item and loop front if necessary
    if(this->front+1 == this->capacity){
        this->front = 0;
    }
    else {
        this->front++;
    }
    this->length--;
}

/* getFront
*  parameters:
*      none
*  return value: front of an ArrayQueue
*
* This function gives the current front of an ArrayQueue
*/
template <class Base>
const Base &ArrayQueue<Base>::getFront() const{
    //make sure that there is a front item
    assert(this->length > 0);
    return this->data[this->front];
}

/* add
*  parameters:
*      none
*  return value: length of an ArrayQueue
*
* This function gives length of an ArrayQueue
*/
template <class Base>
int ArrayQueue<Base>::getLength() const{
    return this->length;
}

/* operator=
*  parameters:
*      q - ArrayQueue to be deep copied into implicit ArrayQueue
*  return value: implicit ArrayQueue
*
* This function overloads the assignment operator for the ArrayQueue class
*/
template <class Base>
const ArrayQueue<Base> &ArrayQueue<Base>::operator=(const ArrayQueue<Base> &q){
    if(this != &q){
        //deallocate memory
        delete [] this->data;
        //deep copy data members
        this->length = q.length;
        this->capacity = q.capacity;
        this->front = q.front;
        this->data = new Base[this->length];
        for(int i = 0; i < q.length; i++){
            this->data[(this->front + i) % this->capacity] =
            q.data[(this->front + i) % this->capacity];
        }
    }
    return *this;
}

/* doubleCapacity
*  parameters:
*      none
*  return value: none
*
* This function doubles the capacity of an ArrayQueue
*/
template <class Base>
void ArrayQueue<Base>::doubleCapacity(){
    int bigCapacity = this->capacity*2;
    //create bigger array
    Base *biggerArray = new Base[bigCapacity];
    //copy data members to bigger array
    for(int i = 0; i < this->length; i++){
        biggerArray[(this->front + i) % bigCapacity] =
        this->data[(this->front + i) % this->capacity];
    }
    //delete and assign smaller array to bigger array
    delete [] this->data;
    this->data = biggerArray;
    //double actual capacity
    this->capacity*=2;
}

#endif
