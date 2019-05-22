/**

@file Queue.h
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Definition of Queue
*/

#ifndef DT019G_QUEUE_H
#define DT019G_QUEUE_H

#include "Song.h"

class Queue {
private:
    Song* arr;
    size_t size;
    size_t front;
    size_t back;
public:

    Queue();

    /**
    Copy constructor
    */
    Queue (Queue const &queue);

    /**
    Destructor
    */
    ~Queue();

    /**
    add song last in queue
    @param song
    */
    void enque(const Song &song);

    /**
    remove and return first item in queue
     @return first song in queue
    */
    Song deque();


    /**
    check if queue is full
     @return true is full
    */
    bool isFull();

    /**
    enlarge the queue
    */
    void enlarge();
    /**
    resets the queue to construtor settings
    */
    void reset();

    /**
    check if queue is emtpty
     @return true if empty
    */
    bool isEmpty();

    /**
    Overload =
     @return *this
    */
    Queue& operator=(const Queue& queue);
};


#endif //DT019G_QUEUE_H
