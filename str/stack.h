#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "node.h"
#include "linked_list.h"
using namespace std;

struct Stack{
    LinkedList list; 
};
Stack Stack_create();
void Stack_destroy(Stack& stack);
void Stack_push_back(Stack& stack, string data);
void Stack_pop(Stack& stack);
string Stack_read(const Stack& stack);
string Stack_peek(const Stack& stack);

#endif