#include <iostream>
#include "stack.h"
#include "linked_list.h"

using namespace std;

Stack Stack_create(){
    Stack stack;
    stack.list = OneLinked_create();
    return stack;
}

void Stack_destroy(Stack& stack) {
    OneLinked_destroy(stack.list);
}

void Stack_push_back(Stack& stack, string data) {
    OneLinked_push_front(stack.list,data);
}

string Stack_pop(Stack& stack){
    return OneLinked_pop_front(stack.list);
}

string Stack_read(const Stack& stack){
    return OneLinked_read_reverse(stack.list);
}