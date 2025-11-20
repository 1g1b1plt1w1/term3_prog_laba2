#pragma once
#include <string>
#include "linked_list.h"
#include "hash_open.h"
using namespace std;

struct LRU {
    size_t cap;
    LinkedList order;
    HashOpen map;
};


LRU LRU_create(size_t capacity);


void LRU_destroy(LRU& c);


void LRU_touch(LRU& c, const string& key);


void LRU_set(LRU& c, const string& key, const string& val);


string LRU_get(LRU& c, const string& key);
