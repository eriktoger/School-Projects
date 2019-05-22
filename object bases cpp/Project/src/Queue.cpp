/**

@file Queue.cpp
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Implementation of Queue
*/
#include "Queue.h"
#include "constants.h"

//Constructor
Queue::Queue (){
    arr = new Song[QUEUE_STARTING_SIZE];
    size = QUEUE_STARTING_SIZE;
    front = 0;
    back  = 0;
}

//copy constructor
Queue::Queue (Queue const &queue){
    size = queue.size;
    arr = new Song[size];
    front = queue.front;
    back  = queue.back;
    for(size_t i = front; i < back; i++){
        arr[i] = queue.arr[i];
    }
}

//Destructor
Queue::~Queue(){
    delete [] arr;
}

//add song last in queue
void Queue::enque(const Song &song) {

    if( isFull() ){
        enlarge();
    }
    arr[back] = song;
    back++;
}

//remove and return first item in queue
Song Queue::deque() {
    if(front < back){
        front++;
        return arr[front-1];
    }
    else{
        return Song();
    }
}

//check if queue is full
bool Queue::isFull(){
    return size <= (back+1);
}

//enlarge the queue
void Queue::enlarge() {
    Song* temp;
    temp = new Song[size + QUEUE_GROWTH];
    for(size_t i = 0; i < size; i++){
        temp[i] = arr[i];
    }
    size +=QUEUE_GROWTH;
    delete [] arr;
    arr = temp;
}

//Overload =
Queue& Queue::operator=(const Queue &queue) {

    if(this != &queue){
        delete [] arr;
        size = queue.size;
        arr = new Song[size];

        front = queue.front;
        back  = queue.back;

        for (size_t i = front; i < back; i++){
            arr[i] = queue.arr[i];
        }
    }

    return *this;
}

//resets the queue to constructor settings
void Queue::reset(){
    delete [] arr;
    arr = new Song[QUEUE_STARTING_SIZE];
    size = QUEUE_STARTING_SIZE;
    front = 0;
    back  = 0;
}

// check if queue is emtpty
bool Queue::isEmpty(){
    return front >= back;
}