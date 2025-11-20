#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "node.h"
#include "linked_list.h"
using namespace std;

struct Queue{
    LinkedList list; 
};
Queue Queue_create();
void Queue_destroy(Queue& queue);
void Queue_push_back(Queue& queue, string data);
void Queue_pop(Queue& queue);
string Queue_read(const Queue& queue);
#endif