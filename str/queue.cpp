#include <iostream>
#include "queue.h"
#include "one_linked_list.h"

using namespace std;

Queue Queue_create(){
    Queue queue;
    queue.list = OneLinked_create();
    return queue;
}

void Queue_destroy(Queue& queue) {
    OneLinked_destroy(queue.list);
}

void Queue_push_back(Queue& queue, string data) {
    OneLinked_push_back(queue.list,data);
}

string Queue_pop(Queue& queue){
    return OneLinked_pop_front(queue.list);
}

string Queue_read(const Queue& queue){
    return OneLinked_read(queue.list);
}