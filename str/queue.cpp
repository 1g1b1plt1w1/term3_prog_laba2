#include <iostream>
#include "queue.h"
#include "node.h"
#include "linked_list.h"

using namespace std;

Queue Queue_create(){
    Queue queue;
    queue.list = Linked_create();
    return queue;
}

void Queue_destroy(Queue& queue) {
    Linked_destroy(queue.list);
}

void Queue_push_back(Queue& queue, string data) {
    Linked_push_back(queue.list,data);
}

void Queue_pop(Queue& queue){
    Linked_pop_front(queue.list);
}

string Queue_read(const Queue& queue){
    return Linked_read(queue.list);
}